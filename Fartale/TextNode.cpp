#include "TextNode.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include "Utilities.h"
TextNode::TextNode(FontManager& fonts)
	: mText("", fonts.get(Fonts::MAIN), 16)
	, mFonts(fonts)
{
	centerOrigin(mText);
}

void TextNode::setText(std::string text)
{
	mText.setString(text);
	centerOrigin(mText);
}

void TextNode::setColor(sf::Color color)
{
	mText.setFillColor(color);
}

void TextNode::setFont(Fonts::ID fontID)
{
	mText.setFont(mFonts.get(fontID));
}

void TextNode::setCharacterSize(std::size_t size)
{
	mText.setCharacterSize(size);
}

void TextNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(mText, states);
}