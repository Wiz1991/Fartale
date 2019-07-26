#include "CommandQueue.h"

void CommandQueue::push(const Command& command)
{
	mQueue.push(command);
}

Command CommandQueue::pop()
{
	Command command = mQueue.front();
	mQueue.pop();

	return command;
}

bool CommandQueue::isEmpty() const
{
	printf("command queue size: %d\n", mQueue.size());
	return mQueue.empty();
}