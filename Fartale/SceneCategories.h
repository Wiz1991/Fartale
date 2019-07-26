#pragma once
namespace Category {
	enum Type {
		NONE = 0,
		BACKGROUND = 1 << 0,
		FOREGROUND = 1 << 1,
		ENEMIES = 1 << 2,
		PLAYER = 1 << 3,
		COLLISIONBLOCK = 1 << 4,
		UI = 1 << 5,
		TOTAL
	};
}
