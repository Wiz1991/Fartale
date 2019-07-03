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

	sf::FloatRect txtBounds = mText.getLocalBounds();
	mText.setOrigin(txtBounds.width / 2, txtBounds.height / 2);

	sf::FloatRect btnBounds = mButton.getLocalBounds();
	mButton.setOrigin(btnBounds.width / 2, btnBounds.height / 2);

	mButton.setPosition(mText.getPosition().x, mText.getPosition().y);

	mText.setFillColor(sf::Color::Black);

	printf("mButton position: X: %f,Y: %f\n", mButton.getPosition().x, mButton.getPosition().y);
	printf("mText position: X: %f,Y:%f\n", mText.getPosition().x, mText.getPosition().y);
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
}

void Button::deselect()
{
	Widget::deselect();
}

void Button::activate()
{
	Widget::activate();

	if (mCallBack)
		mCallBack();

	deactivate();
}

void Button::deactivate()
{
	Widget::deactivate();
}

void Button::setText(std::string text)
{
	mText.setString(text);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mButton, states);
	target.draw(mText, states);
}