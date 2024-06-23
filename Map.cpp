#include "Map.h"
#include <iostream>
#include <fstream>

Map::Map(int width, int height, const Renderer& renderer) : 
	width(width), height(height), levelMap(std::vector<std::vector<int>>(height, std::vector<int>(width, 0))), renderer(renderer)
{
	this->renderer.drawAll(width, height, levelMap);
}

Map::Map(const std::string& filename, const Renderer& renderer) : renderer(renderer)
{
	readFromFile(filename);
	this->renderer.drawAll(width, height, levelMap);
}

bool Map::isWall(int x, int y) const
{
	return !isValidPosition(x, y) || this->levelMap[y][x] == 1;
}

void Map::setWall(int x, int y)
{
	if (isValidPosition(x, y) && this->levelMap[y][x] != 1) {
		this->levelMap[y][x] = 1;
		renderer.drawCell(x, y);
		version++;
	}
}

void Map::setEmpty(int x, int y)
{
	if (isValidPosition(x, y) && this->levelMap[y][x] != 0) {
		this->levelMap[y][x] = 0;
		renderer.drawCell(x, y, sf::Color::Black);
		version++;
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
	version++;
	renderer.drawAll(width, height, levelMap);
}

void Map::fillMap()
{
	this->levelMap = std::vector<std::vector<int>>(height, std::vector<int>(width, 1));
	version++;
	renderer.drawAll(width, height, levelMap);
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

std::vector<int> Map::getNeighbors(int currentIndex) const
{
	int x = currentIndex % width;
	int y = currentIndex / width;
	std::vector<int> neighbors;
	neighbors.reserve(4);

	// Up neighbor
	if (y > 0 && !isWall(x, y - 1)) {
		neighbors.push_back(currentIndex - width);
	}
	// Down neighbor
	if (y < height - 1 && !isWall(x, y + 1)) {
		neighbors.push_back(currentIndex + width);
	}
	// Left neighbor
	if (x > 0 && !isWall(x - 1, y)) {
		neighbors.push_back(currentIndex - 1);
	}
	// Right neighbor
	if (x < width - 1 && !isWall(x + 1, y)) {
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

void Map::writeToFile(const std::string& filename) const
{
	std::ofstream myfile;
	myfile.open(filename, std::ios::trunc);
	myfile << height << " " << width << std::endl;

	for (int i = 0; i < this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			std::string result = this->levelMap[i][j] == 1 ? "#" : " ";
			myfile << result;
		}
		myfile << std::endl;
	}
	myfile.close();
}

void Map::readFromFile(const std::string& filename)
{
	std::string line;
	std::ifstream myfile(filename);
	std::getline(myfile, line);
	this->height = std::stoi(line.substr(0, line.find(' ')));
	this->width = std::stoi(line.substr(line.find(' ') + 1));
	this->levelMap = std::vector<std::vector<int>>(height, std::vector<int>(width, 0));
	int row = 0;
	if (myfile.is_open())
	{
		while (std::getline(myfile, line))
		{
			for (std::string::size_type i = 0; i < line.size(); ++i) {
				this->levelMap[row][i] = line[i] == '#' ? 1 : 0;
			}
			row++;
		}
		myfile.close();
	}
}
