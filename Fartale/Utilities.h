#pragma once
#include <sstream>
namespace sf {
	class Sprite;
	class Text;
}
#include <SFML/Window/Keyboard.hpp>
enum Key {
	W = sf::Keyboard::W,
	S = sf::Keyboard::S,
	D = sf::Keyboard::D,
	A = sf::Keyboard::A,
	UP = sf::Keyboard::Up,
	DOWN = sf::Keyboard::Down,
	LEFT = sf::Keyboard::Left,
	RIGHT = sf::Keyboard::Right,
	ESC = sf::Keyboard::Escape,
	ENTER = sf::Keyboard::Enter,
	RETURN = sf::Keyboard::Return,
	SPACE = sf::Keyboard::Space,
	E = sf::Keyboard::E,
	Q = sf::Keyboard::Q,
	R = sf::Keyboard::R,
	C = sf::Keyboard::C,
	F = sf::Keyboard::F,
	SHIFT = sf::Keyboard::LShift,
	CONTROL = sf::Keyboard::LControl,
	F9 = sf::Keyboard::F9
};
template<typename T>
std::string toString(T value);

void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text& text);

#include "Utilities.inl"