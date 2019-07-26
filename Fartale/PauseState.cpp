#include "PauseState.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "Utilities.h"
#include "Button.h"

PauseState::PauseState(StateStack& stack, Context context)
	: State(stack, context)
	, overlay(static_cast<sf::Vector2f>(context.window->getSize()))
	, mGUIContainer()
{
	overlay.setFillColor({ 5,5,5,170 });

	auto resume = std::make_shared<Button>(*context.textureHolder, *context.fontHolder);
	resume->setPosition(overlay.getGlobalBounds().width / 2, overlay.getGlobalBounds().height / 2 - 40);
	resume->setText("Resume");
	resume->setCallBack([this]() {
		requestStackPop();
		});

	auto MainMenu = std::make_shared<Button>(*context.textureHolder, *context.fontHolder);
	MainMenu->setPosition(overlay.getGlobalBounds().width / 2, overlay.getGlobalBounds().height / 2 + 10);
	MainMenu->setText("Main Menu");
	MainMenu->setCallBack([this]() {
		requestStackClear();
		requestStackPush(States::MENU);
		});

	auto exit = std::make_shared<Button>(*context.textureHolder, *context.fontHolder);
	exit->setPosition(overlay.getGlobalBounds().width / 2, overlay.getGlobalBounds().height / 2 + 80);
	exit->setText("Exit to Desktop");
	exit->setCallBack([this]() {
		requestStackClear();
		});

	mGUIContainer.pack(resume);
	mGUIContainer.pack(MainMenu);
	mGUIContainer.pack(exit);
}

bool PauseState::update(sf::Time dT)
{
	return false;
}

bool PauseState::handleEvent(const sf::Event& event)
{
	mGUIContainer.handleEvent(event);
	if (event.type == sf::Event::KeyReleased && event.key.code == Key::ESC)
		requestStackPop();
	return false;
}

void PauseState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());
	window.draw(overlay);

	window.draw(mGUIContainer);
}