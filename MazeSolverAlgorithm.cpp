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
    std::unordered_set<int> visited;

    int start = mapController.getCellIndexFromCoordinates(startPos);
    int end = mapController.getCellIndexFromCoordinates(endPos);

    queue.push({ 0, start });
    cameFrom[start] = start;
    costSoFar[start] = 0;

    while (!queue.empty()) {
        int current = queue.top().second;
        queue.pop();

        if (current == end) {
            break;
        }

        if (!visited.insert(current).second) {
            continue; // Skip if the node has already been visited
        }

        for (int next : getNeighbors(mapController.getCellCoordinatesFromIndex(current))) {
            if (visited.count(next)) {
                continue; // Now using the visited set for clarity and efficiency
            }

            int newCost = costSoFar[current] + 1;
            if (!costSoFar.count(next) || newCost < costSoFar[next]) {
                costSoFar[next] = newCost;
                int priority = newCost + heuristic(mapController.getCellCoordinatesFromIndex(next), mapController.getCellCoordinatesFromIndex(end));
                queue.push({ priority, next });
                cameFrom[next] = current;
            }
        }
    }

    if (!cameFrom.count(end)) {
        return {}; // Return an empty path if the end was not reached
    }

    std::vector<sf::Vector2i> path;
    for (int current = end; current != start; current = cameFrom[current]) {
        auto cur = mapController.getCellCoordinatesFromIndex(current);
        path.push_back(cur);
    }
    path.push_back(mapController.getCellCoordinatesFromIndex(start));
    std::reverse(path.begin(), path.end());

    //Draw the path
    renderer.drawAll(mapController.getMap().size(), mapController.getMap()[0].size(), mapController.getMap());
    renderer.drawPath(path);

    lastVersion = mapController.getVersion();
    lastPath = path;
    return path;
}

std::vector<int> MazeSolverAlgorithm::getNeighbors(sf::Vector2i current) const
{
    std::vector<sf::Vector2i> possibleNeighbors = { 
        sf::Vector2i(current.x - 1, current.y), 
        sf::Vector2i(current.x + 1, current.y),
        sf::Vector2i(current.x, current.y - 1),
        sf::Vector2i(current.x, current.y + 1)
    };

    std::vector<int> neighbors;
    for (const auto& neighbor : possibleNeighbors) {
		if (!mapController.isWall(neighbor.x, neighbor.y)) {
			neighbors.push_back(mapController.getCellIndexFromCoordinates(neighbor));
		}
	}
    return neighbors;
}

int MazeSolverAlgorithm::heuristic(sf::Vector2i a, sf::Vector2i b) const
{
    return abs(a.x - b.x) + abs(a.y - b.y);
}