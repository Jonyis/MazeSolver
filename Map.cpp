#include "Map.h"
#include <iostream>

Map::Map(int width, int height, const Renderer& renderer) : 
	width(width), height(height), levelMap(std::vector< std::vector<int> >(height, std::vector<int>(width, 0))), renderer(renderer)
{
	this->renderer.drawAll(width, height, cellSize, offset, levelMap);
}

bool Map::isWall(int x, int y)
{
	return isValidPosition(x, y) && this->levelMap[y][x] == 1;
}

void Map::setWall(int x, int y)
{
	if (isValidPosition(x, y)) {
		this->levelMap[y][x] = 1;
		renderer.drawCell(x, y, cellSize, offset);
	}
}

void Map::setEmpty(int x, int y)
{
	if (isValidPosition(x, y)) {
		this->levelMap[y][x] = 0;
		renderer.drawCell(x, y, cellSize, offset, sf::Color::Black);
	}
}

void Map::printMap() const
{
	for (int i = 0; i < this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			std::string result = this->levelMap[i][j] == 1 ? "#" : " ";
			std::cout << result<< " ";
		}
		std::cout << std::endl;
	}
}

void Map::clearMap()
{
	this->levelMap = std::vector<std::vector<int>>(height, std::vector<int>(width, 0));
	renderer.drawAll(width, height, cellSize, offset, levelMap);
}

void Map::fillMap()
{
	this->levelMap = std::vector<std::vector<int>>(height, std::vector<int>(width, 1));
	renderer.drawAll(width, height, cellSize, offset, levelMap);
}

bool Map::isValidPosition(int x, int y) const
{
	if (x < 0 || x >= width || y < 0 || y >= height)
	{
		return false;
	}
	return true;
}

sf::Vector2i Map::getCellCoordinates(sf::Vector2i mousePos) const
{
	return sf::Vector2i((mousePos.x / cellSize) - offset.x, (mousePos.y / cellSize) - offset.y);
}

