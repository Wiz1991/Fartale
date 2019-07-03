#include "MenuState.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "Button.h"

MenuState::MenuState(StateStack& stack, Context context)
	: State(stack, context)
	, mBackground(context.textureHolder->get(Textures::MenuBackground))
{
	//set background texture to fill screen
	context.textureHolder->get(Textures::MenuBackground).setRepeated(true);
	sf::IntRect rect(0, 0, context.window->getSize().x, context.window->getSize().y);
	mBackground.setTextureRect(rect);

	//buttons
	sf::Vector2f windowSize(context.window->getSize());

	auto play = std::make_shared<Button>(*context.textureHolder, *context.fontHolder);
	play->setPosition(windowSize.x / 2, windowSize.y / 2 - 50);
	play->setText("Play");
	play->setCallBack([this]() {
		requestStackPop();
		requestStackPush(States::GAME);
		});
	auto options = std::make_shared<Button>(*context.textureHolder, *context.fontHolder);
	options->setPosition(windowSize.x / 2, windowSize.y / 2 + 2);
	options->setText("Options");
	options->setCallBack([this]() {
		//implement options state
		printf("OPTIONS STATE NOT IMPLEMENTED");
		});

	auto exit = std::make_shared<Button>(*context.textureHolder, *context.fontHolder);
	exit->setPosition(windowSize.x / 2, windowSize.y / 2 + 65);
	exit->setText("Exit");
	exit->setCallBack([this]() {
		requestStackClear();
		});

	mGUIContainer.pack(play);
	mGUIContainer.pack(options);
	mGUIContainer.pack(exit);
}

bool MenuState::update(sf::Time dT)
{
	return true;
}

bool MenuState::handleEvent(const sf::Event& event)
{
	mGUIContainer.handleEvent(event);
	return true;
}

void MenuState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());
	window.draw(mBackground);
	window.draw(mGUIContainer);
}