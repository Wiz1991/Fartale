#pragma once
#include <functional>
#include <SFML/System/Time.hpp>
#include "SceneCategories.h"
#include <cassert>

class SceneNode;
namespace sf {
	class Time;
}
struct Command {
	Command();
	std::function<void(SceneNode&, sf::Time)> action;
	unsigned int category;
};
template<typename GameObject, typename Function>
std::function<void(SceneNode&, sf::Time)> derivedAction(Function fn) {
	return [=](SceneNode& node, sf::Time dT) {
		assert(dynamic_cast<GameObject*>(&node) != nullptr);

		fn(static_cast<GameObject&>(node), dT);
	};
}