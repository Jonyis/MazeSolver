#include "Renderer.h"
#include <iostream>

Renderer::Renderer(sf::RenderWindow& _window) : window(_window) {
}

void Renderer::clear() {
	window.clear();
}

void Renderer::drawAll(int width, int height, int cellSize, sf::Vector2i offset, const std::vector<std::vector<int>>& levelMap) {
	clear();
	drawBorder(0, 0, width, height, cellSize, offset);
	drawMap(cellSize, offset, levelMap);
	window.display();
}

void Renderer::drawCell(int x, int y, int cellSize, sf::Vector2i offset, sf::Color color)
{
	sf::RectangleShape rect(sf::Vector2f(cellSize, cellSize));
	rect.setPosition((x + offset.x) * cellSize, (y + offset.y) * cellSize);
	rect.setFillColor(color);
	window.draw(rect);
	window.display();
}

void Renderer::drawMap(int cellSize, sf::Vector2i offset, const std::vector<std::vector<int>>& mapData)
{
	sf::RectangleShape rect(sf::Vector2f(cellSize, cellSize));
	rect.setFillColor(sf::Color::Yellow);
	for (int i = 0; i < mapData.size(); i++)
	{
		for (int j = 0; j < mapData[i].size(); j++)
		{
			if (mapData[i][j] == 1)
			{
				rect.setPosition((j + offset.x) * cellSize, (i + offset.y) * cellSize);
				window.draw(rect);
			}
		}
	}
}

void Renderer::drawBorder(int x, int y, int width, int height, int cellSize, sf::Vector2i offset, sf::Color color) {
	sf::RectangleShape rect(sf::Vector2f(width * cellSize, height * cellSize));
	rect.setPosition((x + offset.x) * cellSize, (y + offset.y) * cellSize);
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineThickness(10);
	rect.setOutlineColor(color);
	window.draw(rect);
}
