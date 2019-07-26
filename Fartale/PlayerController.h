#pragma once
#include "Command.h"
#include <map>
#include "SFML/Window/Event.hpp"
class CommandQueue;
class PlayerController
{
public:
	enum Action {
		moveLeft,
		moveRight,
		moveUp,
		moveDown,
		jump
	};
	PlayerController();

public:
	void handleEvents(const sf::Event& event, CommandQueue& queue);
	void handleRealTimeInput(CommandQueue& queue);
private:
	void initializeActions();
	bool isRealTimeAction(Action action) const;
private:
	std::map<sf::Keyboard::Key, Action> mKeyboardBindings;
	std::map<Action, Command> mActionBindings;
};
