#include "Widget.h"

Widget::Widget()
	: mIsActive(false)
	, mIsSelected(false)
{
}

bool Widget::isSelected() const
{
	return mIsSelected;
}

void Widget::select()
{
	mIsSelected = true;
}

void Widget::deselect()
{
	mIsSelected = false;
}

void Widget::activate()
{
	mIsActive = true;
}

void Widget::deactivate()
{
	mIsActive = false;
}

bool Widget::isActive() const
{
	return mIsActive;
}