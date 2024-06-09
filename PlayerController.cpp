#include "PlayerController.h"
#include <iostream>

PlayerController::PlayerController(int initialX, int initialY, const Map& mapController, const Renderer& renderer) : 
	posX(initialX), posY(initialY), mapController(mapController), renderer(renderer)
{
	this->renderer.drawPlayer(posX, posY);

}

void PlayerController::Update(int xInput, int yInput)
{
	int horizontalMovement = xInput != 0 ? xInput < 0 ? -1 : 1 : 0;
	int verticalMovement = yInput != 0 ? yInput < 0 ? -1 : 1 : 0;


	int newX = posX + horizontalMovement;
	int newY = posY + verticalMovement;
	if (mapController.isWall(newX, newY)) return;

	// Draw the cell the player was on to erase the player
	renderer.drawCell(posX, posY, sf::Color::Black);

	posX = newX;
	posY = newY;

	renderer.drawPlayer(posX, posY);
}
