#pragma once
#include "Map.h"
class PlayerController
{

	public:
	PlayerController(int initialX, int initialY, const Map& mapController, const Renderer& renderer);
	~PlayerController() = default;

	void update(int xInput, int yInput);
	sf::Vector2i getPosition() const { return sf::Vector2i(posX, posY); }

	private:
		int posX;
		int posY;
		const Map& mapController;
		const Renderer& renderer;
};

