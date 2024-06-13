#pragma once
#include <vector>
#include "Renderer.h"

class Map
{
	public:
		explicit Map(int width, int height, const Renderer& renderer);
		~Map() = default;
		bool isWall(int x, int y) const;
		void setWall(int x, int y);
		void setEmpty(int x, int y);
		void printMap() const;
		void clearMap();
		void fillMap();
		std::vector<std::vector<int>> getMap() const { return levelMap; }
		sf::Vector2i getCellCoordinates(sf::Vector2i mousePos) const;
		sf::Vector2i getCellCoordinatesFromIndex(int index) const;
		int getCellIndexFromCoordinates(sf::Vector2i coordinates) const;
		int getVersion() const { return version; }

	private:
		int width;
		int height;
		std::vector<std::vector<int>> levelMap;
		const Renderer& renderer;
		int version = 0;
		bool isValidPosition(int x, int y) const;
};

