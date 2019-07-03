#include "MenuState.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "Button.h"

MenuState::MenuState(StateStack& stack, Context context)
	: State(stack, context)
	, mBackground(context.textureHolder->get(Textures::blueButtons))
{
	auto play = std::make_shared<Button>(*context.textureHolder, *context.fontHolder);
	play->setPosition(300, 300);
	play->setText("---HEY---");
	play->setCallBack([this]() {
		//enter game state
		printf("CALLBACK NOT SET");
		});
	mGUIContainer.pack(play);
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
	//window.draw(mBackground);
	window.draw(mGUIContainer);
}