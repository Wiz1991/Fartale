#include "Button.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include "Utilities.h"

Button::Button(TextureManager& textures, FontManager& fonts)
	: mText("", fonts.get(Fonts::MAIN), 12)
	, mNormalTexture(textures.get(Textures::blueButtons))
	, mButton()

{
	mButton.setTextureRect(sf::IntRect(0, 0, 190, 49));
	mButton.setTexture(mNormalTexture);

	centerOrigin(mButton);
	centerOrigin(mText);

	mText.setFillColor(sf::Color::Black);
}
void Button::setCallBack(CallBack callback)
{
	mCallBack = std::move(callback);
}
bool Button::isSelectable() const
{
	return true;
}

void Button::handleEvent(const sf::Event&)
{
}

void Button::select()
{
	Widget::select();
	setTextColor(sf::Color::White);
}

void Button::deselect()
{
	Widget::deselect();
	setTextColor(sf::Color::Black);
}

void Button::activate()
{
	Widget::activate();

	mButton.setTextureRect(sf::IntRect(0, 49, 190, 45)); //pressed texture

	if (mCallBack)
		mCallBack();

	deactivate();
}

void Button::deactivate()
{
	Widget::deactivate();

	mButton.setTextureRect(sf::IntRect(0, 0, 190, 49)); //normal texture
}

void Button::setText(std::string text)
{
	mText.setString(text);
	centerOrigin(mText);
}

void Button::setTextColor(sf::Color color)
{
	mText.setFillColor(color);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mButton, states);
	target.draw(mText, states);
}