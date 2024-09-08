#include "AutomatedPlayerController.h"
#include <iostream>

AutomatedPlayerController::AutomatedPlayerController(int x, int y, const Map& mapController, const Renderer& renderer) : 
	mapController(mapController), renderer(renderer), playerController(x, y, mapController, renderer)
{
	instructions.push_back(std::make_pair(PlayerCondition::IS_EMPTY_RIGHT, PlayerAction::MOVE_RIGHT));
	instructions.push_back(std::make_pair(PlayerCondition::IS_EMPTY_UP, PlayerAction::MOVE_UP));
	instructions.push_back(std::make_pair(PlayerCondition::IS_EMPTY_DOWN, PlayerAction::MOVE_DOWN));
	instructions.push_back(std::make_pair(PlayerCondition::IS_EMPTY_LEFT, PlayerAction::MOVE_LEFT));
}

void AutomatedPlayerController::update()
{
    for (const auto& instruction : instructions) {
		if (checkCondition(instruction.first)) {
			performAction(instruction.second);
			return;
		}
    }
}

bool AutomatedPlayerController::checkCondition(PlayerCondition condition) const
{
	auto pos = playerController.getPosition();
	switch (condition) {
		case PlayerCondition::IS_EMPTY_UP:
			std::cout << "Checking if empty up" << std::endl;
			return !mapController.isWall(pos.x, pos.y - 1);
		case PlayerCondition::IS_EMPTY_DOWN:
			std::cout << "Checking if empty down" << std::endl;
			return !mapController.isWall(pos.x, pos.y + 1);
		case PlayerCondition::IS_EMPTY_LEFT:
			std::cout << "Checking if empty left" << std::endl;
			return !mapController.isWall(pos.x - 1, pos.y);
		case PlayerCondition::IS_EMPTY_RIGHT:
			std::cout << "Checking if empty right" << std::endl;
			return !mapController.isWall(pos.x + 1, pos.y);
		default:
			return false;
	}
}

void AutomatedPlayerController::performAction(PlayerAction action)
{
	switch (action) {
	case PlayerAction::MOVE_UP:
		std::cout << "Moving up" << std::endl;
		playerController.update(0, -1);
		break;
	case PlayerAction::MOVE_DOWN:
		std::cout << "Moving down" << std::endl;
		playerController.update(0, 1);
		break;
	case PlayerAction::MOVE_LEFT:
		std::cout << "Moving left" << std::endl;
		playerController.update(-1, 0);
		break;
	case PlayerAction::MOVE_RIGHT:
		std::cout << "Moving right" << std::endl;
		playerController.update(1, 0);
		break;
	default:
		break;
	}
}

std::string AutomatedPlayerController::playerConditionToString(PlayerCondition condition) const
{
    switch (condition) {
        case PlayerCondition::IS_EMPTY_UP: return "IS_EMPTY_UP";
        case PlayerCondition::IS_EMPTY_DOWN: return "IS_EMPTY_DOWN";
        case PlayerCondition::IS_EMPTY_LEFT: return "IS_EMPTY_LEFT";
        case PlayerCondition::IS_EMPTY_RIGHT: return "IS_EMPTY_RIGHT";
        default: return "UNKNOWN_CONDITION";
    }
}

std::string AutomatedPlayerController::playerActionToString(PlayerAction action) const
{
    switch (action) {
    case PlayerAction::MOVE_UP: return "MOVE_UP";
    case PlayerAction::MOVE_DOWN: return "MOVE_DOWN";
    case PlayerAction::MOVE_LEFT: return "MOVE_LEFT";
    case PlayerAction::MOVE_RIGHT: return "MOVE_RIGHT";
    default: return "UNKNOWN_ACTION";
    }
}
