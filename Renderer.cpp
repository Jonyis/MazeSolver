#include "Renderer.h"

Renderer::Renderer(sf::RenderWindow& _window) : window(_window) {
}

void Renderer::clear() const
{
	window.clear();
}

sf::Vector2i Renderer::getMapCoordinates(sf::Vector2i mousePos) const
{
	return sf::Vector2i((mousePos.x / cellSize) - offset.x, (mousePos.y / cellSize) - offset.y);
}

void Renderer::drawAll(int width, int height, const std::vector<std::vector<int>>& levelMap) const
{
	clear();
	drawBorder(0, 0, width, height);
	drawMap(levelMap);
	window.display();
}

void Renderer::drawCell(int x, int y, sf::Color color) const
{
	sf::RectangleShape rect(sf::Vector2f(cellSize, cellSize));
	rect.setPosition((x + offset.x) * cellSize, (y + offset.y) * cellSize);
	rect.setFillColor(color);
	window.draw(rect);
	window.display();
}

void Renderer::drawPlayer(int x, int y, sf::Color color) const
{
	sf::CircleShape circle(cellSize / 2);
	circle.setFillColor(color);
	circle.setPosition((x + offset.x) * cellSize, (y + offset.y) * cellSize);
	window.draw(circle);
	window.display();
}

void Renderer::drawPath(const std::vector<sf::Vector2i>& path, sf::Color color) const
{
	sf::RectangleShape rect(sf::Vector2f(cellSize, cellSize));
	rect.setFillColor(color);
	for (const auto& cell : path)
	{
		rect.setPosition((cell.x + offset.x) * cellSize, (cell.y + offset.y) * cellSize);
		window.draw(rect);
	}
	window.display();

}

void Renderer::drawMap(const std::vector<std::vector<int>>& mapData) const
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

void Renderer::drawBorder(int x, int y, int width, int height, sf::Color color) const
{
	sf::RectangleShape rect(sf::Vector2f(width * cellSize, height * cellSize));
	rect.setPosition((x + offset.x) * cellSize, (y + offset.y) * cellSize);
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineThickness(10);
	rect.setOutlineColor(color);
	window.draw(rect);
}
