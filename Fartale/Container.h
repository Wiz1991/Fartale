#pragma once
#include "Widget.h"
#include <vector>
class Container : public Widget
{
public:
	Container();
	void pack(Widget::Ptr widget);
	virtual void handleEvent(const sf::Event& event);
	virtual bool isSelectable() const;
private:
	bool hasSelected();

	void selectNext();
	void selextPrevious();
	void select(std::size_t index);
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;

private:
	int mSelectedChild;
	std::vector<Widget::Ptr> mChildren;
};
