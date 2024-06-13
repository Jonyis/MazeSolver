#pragma once
#include "Map.h"
class MazeSolverAlgorithm
{
	public:
	MazeSolverAlgorithm(sf::Vector2i startPos, sf::Vector2i endPos, Map& mapController, const Renderer& renderer);
	~MazeSolverAlgorithm() = default;

	std::vector<sf::Vector2i> solve() const;

	private:
		Map& mapController;
		const Renderer& renderer;
		sf::Vector2i startPos;
		sf::Vector2i endPos;
		mutable std::vector<sf::Vector2i> lastPath;
		mutable int lastVersion = -1;


		int heuristic(int a, int b) const;
};

