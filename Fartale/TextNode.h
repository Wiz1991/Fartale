#pragma once
#include "SceneNode.h"
#include "ResourceIdentifiers.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

class TextNode : public SceneNode
{
public:
	TextNode(FontManager& fonts);

	void setText(std::string text);
	void setColor(sf::Color color);
	void setFont(Fonts::ID fontID);
	void setCharacterSize(std::size_t size);

private:
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states)const;

private:
	sf::Text mText;
	FontManager& mFonts;
};
