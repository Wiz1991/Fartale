#pragma once
#include "Widget.h"
#include <functional>
#include "ResourceIdentifiers.h"
#include "ResourceHolder.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <functional>
#include <string>

class Button : public Widget
{
public:
	typedef std::shared_ptr<Button> Ptr;
	typedef std::function<void()> CallBack;

	Button(TextureManager& textures, FontManager& fonts);

	void setCallBack(CallBack callback);

	virtual bool isSelectable() const;
	virtual void handleEvent(const sf::Event&);

	virtual void select();
	virtual void deselect();

	virtual void activate();
	virtual void deactivate();

	void setText(std::string text);
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
private:
	sf::Sprite mButton;
	sf::Texture& mNormalTexture;

	sf::Text mText;

	CallBack mCallBack;
};
