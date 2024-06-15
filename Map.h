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
		std::vector<int> getMap() const { return mapData; }
		sf::Vector2i getCellCoordinates(sf::Vector2i mousePos) const;
		sf::Vector2i getCellCoordinatesFromIndex(int index) const;
		int getCellIndexFromCoordinates(sf::Vector2i coordinates) const;
		int getCellIndexFromCoordinates(int x, int y) const;
		int getVersion() const { return version; }
		std::vector<int> getNeighbors(int currentIndex) const;
		int distance(int indexA, int indexB) const;
		int getWidth() const { return width; }
		int getHeight() const { return height; }

	private:
		int width;
		int height;
		std::vector<int> mapData;
		const Renderer& renderer;
		int version = 0;
		bool isValidPosition(int x, int y) const;
		bool isValidPosition(int index) const;
};

