#pragma once
#include "State.h"

#include <vector>
#include <functional>
#include <map>
class StateStack
{
public:
	enum Action {
		Push,
		Pop,
		Clear
	};
public:
	StateStack(State::Context context);

	template<typename T>
	void registerState(States::ID stateID);

	void update(sf::Time dT);
	void draw();
	void handleEvents(const sf::Event& event);

	void pushState(States::ID stateID);
	void popState();
	void clearStates();

	bool isEmpty() const;
private:
	State::Ptr createState(States::ID stateID);
	void applyPendingChanges();
private:
	struct PendingChange {
		PendingChange(Action action, States::ID id = States::NONE);

		Action mAction;
		States::ID stateID;
	};
private:
	std::vector<State::Ptr> mStateStack;
	std::vector<PendingChange> mPendingList;
	std::map<States::ID, std::function<State::Ptr()>> mFactories;
	State::Context mContext;
};

template<typename T>
void StateStack::registerState(States::ID stateID)
{
	mFactories[stateID] = [this]() {
		return State::Ptr(new T(*this, mContext));
	};
}
