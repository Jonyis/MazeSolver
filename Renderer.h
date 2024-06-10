#pragma once
#include <SFML/Graphics.hpp>

class Renderer
{
	public:
		explicit Renderer(sf::RenderWindow& _window);
		void clear() const;
		sf::Vector2i getMapCoordinates(sf::Vector2i mousePos) const;
		void drawAll(int width, int height, const std::vector<std::vector<int>>& levelMap) const;
		void drawCell(int x, int y, sf::Color color = sf::Color::Yellow) const;
		void drawPlayer(int x, int y, sf::Color color = sf::Color::Green) const;
		void drawPath(const std::vector<sf::Vector2i>& path, sf::Color color = sf::Color::Cyan) const;
	private:
		sf::RenderWindow& window;
		int cellSize = 30;
		sf::Vector2i offset = { 2, 2 };
		void drawMap(const std::vector<std::vector<int>>& mapData) const;
		void drawBorder(int x, int y, int width, int height, sf::Color color = sf::Color::White) const;

};

