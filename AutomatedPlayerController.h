#pragma once
#include "Map.h"
#include "PlayerController.h"
#include "Renderer.h"

class AutomatedPlayerController
{
	public:
	AutomatedPlayerController(int x, int y, const Map& mapController, const Renderer& renderer);
	~AutomatedPlayerController() = default;

	void update();

	enum class PlayerCondition
	{
		IS_EMPTY_UP,
		IS_EMPTY_DOWN,
		IS_EMPTY_LEFT,
		IS_EMPTY_RIGHT
	};

	enum class PlayerAction
	{
		MOVE_UP,
		MOVE_DOWN,
		MOVE_LEFT,
		MOVE_RIGHT,
		NO_MOVE
	};

	private:
		const Map& mapController;
		const Renderer& renderer;
		PlayerController playerController;
		std::vector<std::pair<PlayerCondition, PlayerAction>> instructions;

		bool checkCondition(PlayerCondition condition) const;
		void performAction(PlayerAction action);

		std::string playerConditionToString(PlayerCondition condition) const;
		std::string playerActionToString(PlayerAction action) const;
};




