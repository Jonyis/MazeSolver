#include "MazeSolverAlgorithm.h"
#include <queue>
#include <unordered_map>
#include <unordered_set>

MazeSolverAlgorithm::MazeSolverAlgorithm(sf::Vector2i startPos, sf::Vector2i endPos, Map& mapController, const Renderer& renderer)
	: mapController(mapController), renderer(renderer), startPos(startPos), endPos(endPos)
{
}

std::vector<sf::Vector2i> MazeSolverAlgorithm::solve() const
{
    if (mapController.getVersion() == lastVersion) {
		return lastPath;
	}

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> queue;
    std::unordered_map<int, int> cameFrom;
    std::unordered_map<int, int> costSoFar;
    std::unordered_map<int, int> heuristicCache;
    std::unordered_set<int> visited;

    int start = mapController.getCellIndexFromCoordinates(startPos);
    int end = mapController.getCellIndexFromCoordinates(endPos);

    queue.push({ 0, start });
    cameFrom[start] = start;
    costSoFar[start] = 0;
    heuristicCache[start] = heuristic(start, end);

    while (!queue.empty()) {
        int current = queue.top().second;
        queue.pop();

        if (current == end) {
            break;
        }

        if (!visited.insert(current).second) {
            continue; // Skip if the node has already been visited
        }

        for (int next : mapController.getNeighbors(current)) {
            if (visited.count(next)) {
                continue;
            }

            int newCost = costSoFar[current] + 1;
            if (!costSoFar.count(next) || newCost < costSoFar[next]) {
                costSoFar[next] = newCost;
                if (!heuristicCache.count(next)) {
                    heuristicCache[next] = heuristic(next, end);
                }
                int priority = newCost + heuristicCache[next];
                queue.push({ priority, next });
                cameFrom[next] = current;
            }
        }
    }

    if (!cameFrom.count(end)) {
        return {}; // Return an empty path if the end was not reached
    }

    std::vector<int> pathIndexes;
    for (int current = end; current != start; current = cameFrom[current]) {
        pathIndexes.push_back(current);
    }
    pathIndexes.push_back(start);

    std::vector<sf::Vector2i> path;
    std::transform(pathIndexes.rbegin(), pathIndexes.rend(), std::back_inserter(path),
        [this](int index) { return mapController.getCellCoordinatesFromIndex(index); });

    //Draw the path
    renderer.drawAll(mapController.getWidth(), mapController.getHeight(), mapController.getMap());
    renderer.drawPath(path);

    lastVersion = mapController.getVersion();
    lastPath = path;
    return path;
}

int MazeSolverAlgorithm::heuristic(int a, int b) const
{
    return mapController.distance(a, b);
}