#include "StateStack.h"

StateStack::StateStack(State::Context context)
	: mContext(context)
	, mStateStack()
	, mPendingList()
	, mFactories()
{
}

void StateStack::update(sf::Time dT)
{
	for (auto& it : mStateStack) {
		if (!it->update(dT))
			break;
	}
	applyPendingChanges();
}

void StateStack::draw()
{
	for (auto& it : mStateStack) {
		it->draw();
	}
}

void StateStack::handleEvents(const sf::Event& event)
{
	for (auto& it : mStateStack) {
		if (!it->handleEvents(event))
			break;
	}
}

void StateStack::pushState(States::ID stateID)
{
	mPendingList.push_back(PendingChange(Action::Push, stateID));
}

void StateStack::popState()
{
	mPendingList.push_back(PendingChange(Action::Pop));
}

void StateStack::clearStates()
{
	mPendingList.push_back(PendingChange(Action::Clear));
}

bool StateStack::isEmpty() const
{
	return mStateStack.empty();
}

State::Ptr StateStack::createState(States::ID stateID)
{
	auto found = mFactories.find(stateID);

	return found->second();
}

void StateStack::applyPendingChanges()
{
	for (auto& change : mPendingList) {
		switch (change.mAction) {
		case Action::Push:
			mStateStack.push_back(createState(change.stateID));
		case Action::Pop:
			mStateStack.pop_back();
		case Action::Clear:
			mStateStack.clear();
		}
	}
}

StateStack::PendingChange::PendingChange(Action action, States::ID id)
	: mAction(action)
	, stateID(id)
{
}