#include "State.h"
#include "StateStack.h"
State::State(StateStack& stack, Context context)
	: mStack(&stack)
	, mContext(context)
{
}

void State::requestStackPush(States::ID ID)
{
	mStack->pushState(ID);
}

void State::requestStackClear()
{
	mStack->clearStates();
}

void State::requestStackPop()
{
	mStack->popState();
}

State::Context State::getContext()
{
	return mContext;
}

State::Context::Context(sf::RenderWindow& mWindow, TextureManager& mTextureManager, FontManager& mFontManager)
	: window(&mWindow)
	, textureHolder(&mTextureManager)
	, fontHolder(&mFontManager)
{
}