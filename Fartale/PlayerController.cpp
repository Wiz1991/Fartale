#include "PlayerController.h"
#include "CommandQueue.h"
#include "Player.h"
#include "SceneCategories.h"
struct Controller {
	Controller(float vX = 0, float vY = 0)
		: velocity(vX, vY)
	{
	}

	void operator() (Player& player, sf::Time) const {
		player.accelerate(velocity);
	}
private:
	sf::Vector2f velocity;
};
PlayerController::PlayerController()
{
	mKeyboardBindings[sf::Keyboard::Key::A] = moveLeft;
	mKeyboardBindings[sf::Keyboard::Key::D] = moveRight;
	mKeyboardBindings[sf::Keyboard::Key::S] = moveDown;
	mKeyboardBindings[sf::Keyboard::Space] = jump;
	//BY DEFAULT CATEGORY SHOULD BE ONLY PLAYER
	mActionBindings[moveLeft].category = Category::PLAYER;
	mActionBindings[moveRight].category = Category::PLAYER;
	mActionBindings[moveDown].category = Category::PLAYER;
	mActionBindings[jump].category = Category::PLAYER;

	initializeActions();
}
void PlayerController::handleEvents(const sf::Event& event, CommandQueue& queue)
{
	if (event.type == sf::Event::KeyPressed) {
		auto& key = event.key.code;
		auto found = mKeyboardBindings.find(key);
		if (found != mKeyboardBindings.end() && !isRealTimeAction(found->second)) {
			queue.push(mActionBindings[found->second]);
		}
	}
}

void PlayerController::handleRealTimeInput(CommandQueue& queue)
{
	for (auto key : mKeyboardBindings) {
		if (sf::Keyboard::isKeyPressed(key.first) && isRealTimeAction(key.second)) {
			queue.push(mActionBindings[key.second]);
		}
	}
}

void PlayerController::initializeActions()
{
	const float playerSpeed = 180;
	mActionBindings[moveLeft].action = derivedAction<Player>(Controller(-playerSpeed, 0));
	mActionBindings[moveRight].action = derivedAction<Player>(Controller(+playerSpeed, 0));
	mActionBindings[jump].action = [&](SceneNode& node, sf::Time dT) {
		assert(dynamic_cast<Player*>(&node) != nullptr);
		auto& player = static_cast<Player&>(node);
		if (player.isJumping() || player.isFalling()) return;
		if (!player.isJumping()) {
			player.setJumping(true);
			player.setGravity(64);
		}
	};

	mActionBindings[moveDown].action = derivedAction<Player>(Controller(0, playerSpeed));
}

bool PlayerController::isRealTimeAction(Action action) const
{
	switch (action) {
	case moveRight:
	case moveLeft:
	case moveDown:
	case moveUp:

		return true;
	default:
		return false;
	}
}