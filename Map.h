#pragma once
#include <vector>
#include "Renderer.h"

class Map
{
	public:
		explicit Map(int width, int height, const Renderer& renderer);
		~Map() = default;
		bool isWall(int x, int y);
		void setWall(int x, int y);
		void setEmpty(int x, int y);
		void printMap() const;
		void clearMap();
		void fillMap();
		std::vector<std::vector<int>> getMap() const { return levelMap; }
		sf::Vector2i getCellCoordinates(sf::Vector2i mousePos) const;

	private:
		int width;
		int height;
		int cellSize = 10;
		sf::Vector2i offset = { 2, 2 };
		std::vector<std::vector<int>> levelMap;
		Renderer renderer;

		bool isValidPosition(int x, int y) const;
};

