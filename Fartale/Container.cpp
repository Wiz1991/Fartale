#include "Container.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include "Utilities.h"
Container::Container()
	: mSelectedChild(-1)
	, mChildren()
{
}

void Container::pack(Widget::Ptr widget)
{
	mChildren.push_back(std::move(widget));
	if (!hasSelected() && mChildren[mChildren.size() - 1]->isSelectable())
		select(mChildren.size() - 1);
}

void Container::handleEvent(const sf::Event& event)
{
	if (hasSelected() && mChildren[mSelectedChild]->isActive())
		mChildren[mSelectedChild]->handleEvent(event);

	if (event.type == sf::Event::KeyReleased) {
		if (event.key.code == Key::ENTER || event.key.code == Key::SPACE) {
			if (hasSelected())
				mChildren[mSelectedChild]->activate();
		}
		if (event.key.code == Key::S || event.key.code == Key::DOWN) {
			selectNext();
		}
		if (event.key.code == Key::W || event.key.code == Key::UP) {
			selextPrevious();
		}
	}
}

bool Container::isSelectable() const
{
	return false;
}

bool Container::hasSelected()
{
	return mSelectedChild >= 0;
}

void Container::selectNext()
{
	if (mSelectedChild < 0) return;

	int next = mSelectedChild;
	do {
		next = (next + 1) % mChildren.size();
	} while (!mChildren[next]->isSelectable());
	select(next);
}

void Container::selextPrevious()
{
	if (mSelectedChild < 0) return;

	int prev = mSelectedChild;
	do {
		prev = (prev + mChildren.size() - 1) % mChildren.size();
	} while (!mChildren[prev]->isSelectable());

	select(prev);
}

void Container::select(std::size_t index)
{
	if (mChildren[index]->isSelectable()) {
		if (hasSelected())
			mChildren[mSelectedChild]->deselect();
		mSelectedChild = index;
		mChildren[index]->select();
	}
}

void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	for (const auto& it : mChildren) {
		target.draw(*it, states);
	}
}