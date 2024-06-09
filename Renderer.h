#pragma once
#include <SFML/Graphics.hpp>

class Renderer
{
	public:
		explicit Renderer(sf::RenderWindow& _window);
		void clear();
		void drawAll(int width, int height, int cellSize, sf::Vector2i offset, const std::vector<std::vector<int>>& levelMap);
		void drawCell(int x, int y, int cellSize, sf::Vector2i offset, sf::Color color = sf::Color::Yellow);
	private:
		sf::RenderWindow& window;

		void drawMap(int cellSize, sf::Vector2i offset, const std::vector<std::vector<int>>& mapData);
		void drawBorder(int x, int y, int width, int height, int cellSize, sf::Vector2i offset, sf::Color color = sf::Color::White);

};

