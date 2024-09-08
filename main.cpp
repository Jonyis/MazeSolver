#include <SFML/Graphics.hpp>
#include <iostream>
#include "Renderer.h"
#include "Map.h"
#include "PlayerController.h"
#include "MazeSolverAlgorithm.h"
#include "AutomatedPlayerController.h"

void handleWindowEvents(sf::RenderWindow& window, Map& map, PlayerController& playerController, const MazeSolverAlgorithm& mazeSolver, bool& isPaused, bool& isBuilding, bool& isErasing);

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(500 * 2, 2 * 500), "", sf::Style::Default, settings);

    unsigned int fpsLimit = 60;
    window.setFramerateLimit(fpsLimit);

    Renderer renderer(window);
    //Map levelMap(10, 10, renderer);
    Map levelMap("map.txt", renderer);
    PlayerController player(2, 2, levelMap, renderer);
    AutomatedPlayerController autoPlayer(2, 2, levelMap, renderer);
    MazeSolverAlgorithm mazeSolver(sf::Vector2i(2, 2), sf::Vector2i(28, 20), levelMap, renderer);

    bool isPaused = true;
    bool isBuilding = false;
    bool isErasing = false;

    while (window.isOpen())
    {
        handleWindowEvents(window, levelMap, player, mazeSolver, isPaused, isBuilding, isErasing);

        if (isBuilding) {
            auto mousePos = sf::Mouse::getPosition(window);
            auto cellCords = renderer.getMapCoordinates(mousePos);
            levelMap.setWall(cellCords.x, cellCords.y);
        }
        else if (isErasing) {
            auto mousePos = sf::Mouse::getPosition(window);
            auto cellCords = renderer.getMapCoordinates(mousePos);
            levelMap.setEmpty(cellCords.x, cellCords.y);
        }

        if (!isPaused) {
			autoPlayer.update();
		}
    }

    return 0;
}


void handleWindowEvents(sf::RenderWindow& window, Map& levelMap, PlayerController& playerController, const MazeSolverAlgorithm& mazeSolver, bool& isPaused, bool& isBuilding, bool& isErasing) {
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
                case sf::Keyboard::T:
                    levelMap.writeToFile("map.txt");
                    break;
                case sf::Keyboard::S:
					mazeSolver.solve();
                    playerController.update(0, 0); // Force to re-draw player
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
                case sf::Keyboard::Right:
                    playerController.update(1, 0);
                    break;
                case sf::Keyboard::Left:
                    playerController.update(-1, 0);
                    break;
                case sf::Keyboard::Up:
                    playerController.update(0, -1);
                    break;
                case sf::Keyboard::Down:
                    playerController.update(0, 1);
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