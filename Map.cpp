#include "Map.h"
#include <iostream>

Map::Map(int width, int height, const Renderer& renderer) : 
	width(width), height(height), mapData(std::vector<int>(width* height, 0)), renderer(renderer)
{
	this->renderer.drawAll(width, height, mapData);
}

bool Map::isWall(int x, int y) const
{
	return !isValidPosition(x, y) || mapData[getCellIndexFromCoordinates(x, y)] == 1;
}

void Map::setWall(int x, int y)
{
	int index = getCellIndexFromCoordinates(x, y);
	if (isValidPosition(index) && mapData[index] != 1) {
		mapData[index] = 1;
		renderer.drawCell(x, y);
		version++;
	}
}

void Map::setEmpty(int x, int y)
{
	int index = getCellIndexFromCoordinates(x, y);
	if (isValidPosition(index) && mapData[index] != 0) {
		mapData[index] = 0;
		renderer.drawCell(x, y, sf::Color::Black);
		version++;
	}
}

void Map::printMap() const
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			std::string result = this->mapData[i * width + j] == 1 ? "#" : " ";
			std::cout << result << " ";
		}
		std::cout << std::endl;
	}
}

void Map::clearMap()
{
	this->mapData = std::vector<int>(width * height, 0);
	version++;
	renderer.drawAll(width, height, mapData);
}

void Map::fillMap()
{
	this->mapData = std::vector<int>(width * height, 1);
	version++;
	renderer.drawAll(width, height, mapData);
}

bool Map::isValidPosition(int x, int y) const
{
	if (x < 0 || x >= width || y < 0 || y >= height)
	{
		return false;
	}
	return true;
}

bool Map::isValidPosition(int index) const
{
	if (index < 0 || index >= width * height)
	{
		int x = index % width;
		int y = index / width;
		return isValidPosition(x, y);
	}
	return true;
}

sf::Vector2i Map::getCellCoordinates(sf::Vector2i mousePos) const
{
	return renderer.getMapCoordinates(mousePos);
}

sf::Vector2i Map::getCellCoordinatesFromIndex(int index) const
{
	int x = index % width;
	int y = index / width;
	return sf::Vector2i(x, y);
}

int Map::getCellIndexFromCoordinates(sf::Vector2i coordinates) const
{
	return coordinates.y * width + coordinates.x;
}

int Map::getCellIndexFromCoordinates(int x, int y) const
{
	return y * width + x;
}

std::vector<int> Map::getNeighbors(int currentIndex) const
{
	int x = currentIndex % width;
	int y = currentIndex / width;
	std::vector<int> neighbors;
	neighbors.reserve(4);

	// Up neighbor
	if (!isWall(x, y - 1)) {
		neighbors.push_back(currentIndex - width);
	}
	// Down neighbor
	if (!isWall(x, y + 1)) {
		neighbors.push_back(currentIndex + width);
	}
	// Left neighbor
	if (!isWall(x - 1, y)) {
		neighbors.push_back(currentIndex - 1);
	}
	// Right neighbor
	if (!isWall(x + 1, y)) {
		neighbors.push_back(currentIndex + 1);
	}

	return neighbors;
}


int Map::distance(int indexA, int indexB) const
{
	int xA = indexA % width;
	int yA = indexA / width;
	int xB = indexB % width;
	int yB = indexB / width;

	return abs(xA - xB) + abs(yA - yB);

}
