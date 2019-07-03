#pragma once
#include "StateIdentifiers.h"
#include "ResourceIdentifiers.h"
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>
namespace sf {
	class RenderWindow;
}
class StateStack;

class State
{
public:
	typedef std::unique_ptr<State> Ptr;
	struct Context {
		Context(sf::RenderWindow& mWindow, TextureManager& mTextureManager, FontManager& mFontManager);

		sf::RenderWindow* window;
		TextureManager* textureHolder;
		FontManager* fontHolder;
	};
	State(StateStack& stack, Context context);

	virtual void draw() = 0;
	virtual bool update(sf::Time dT) = 0;
	virtual bool handleEvent(const sf::Event& event) = 0;

protected:
	void requestStackPush(States::ID ID);
	void requestStackClear();
	void requestStackPop();

	Context getContext();

private:
	StateStack* mStack;
	Context mContext;
};
