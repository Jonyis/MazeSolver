#include <SFML/Graphics.hpp>
#include <iostream>
#include "Renderer.h"
#include "Map.h"
#include "SimulationStatistics.h"

void handleWindowEvents(sf::RenderWindow& window, Map& particleManager, bool& isPaused, bool& isBuilding, bool& isErasing);

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(500 * 2, 2 * 500), "", sf::Style::Default, settings);

    Renderer renderer(window);
    Map levelMap(25*3, 25*3, renderer);

    bool isPaused = false;
    bool isBuilding = false;
    bool isErasing = false;

    while (window.isOpen())
    {
        handleWindowEvents(window, levelMap, isPaused, isBuilding, isErasing);

        if (isBuilding) {
            auto mousePos = sf::Mouse::getPosition(window);
            auto cellCords = levelMap.getCellCoordinates(mousePos);
            levelMap.setWall(cellCords.x, cellCords.y);
        }
        else if (isErasing) {
            auto mousePos = sf::Mouse::getPosition(window);
            auto cellCords = levelMap.getCellCoordinates(mousePos);
            levelMap.setEmpty(cellCords.x, cellCords.y);
        }
    }

    return 0;
}


void handleWindowEvents(sf::RenderWindow& window, Map& levelMap, bool& isPaused, bool& isBuilding, bool& isErasing) {
    sf::Event event;

    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Escape:
				    window.close();
				    break;
                case sf::Keyboard::P:
					levelMap.printMap();
					break;
                case sf::Keyboard::Space: 
                    isPaused = !isPaused;
                    break;
                case sf::Keyboard::R:
                    levelMap.clearMap();
					break;
                case sf::Keyboard::F:
                    levelMap.fillMap();
                    break;
                default: break;
            }
		}

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) isBuilding = true;
            if (event.mouseButton.button == sf::Mouse::Right) isErasing = true;
        }
        else if (event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == sf::Mouse::Left) isBuilding = false;
            if (event.mouseButton.button == sf::Mouse::Right) isErasing = false;
        }
    }
}