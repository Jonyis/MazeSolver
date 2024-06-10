#pragma once
#include "Map.h"
class MazeSolverAlgorithm
{
	public:
	MazeSolverAlgorithm(sf::Vector2i startPos, sf::Vector2i endPos, Map& mapController, const Renderer& renderer);
	~MazeSolverAlgorithm() = default;

	std::vector<sf::Vector2i> solve() const;

	std::vector<int> getNeighbors(sf::Vector2i current) const;

	int heuristic(sf::Vector2i a, sf::Vector2i b) const;

	private:
		Map& mapController;
		const Renderer& renderer;
		sf::Vector2i startPos;
		sf::Vector2i endPos;
		std::vector<sf::Vector2i> path;
};

