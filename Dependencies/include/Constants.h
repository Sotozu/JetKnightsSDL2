#pragma once

namespace jks {

	struct Position {
		float x   { 0 };
		float y   { 0 };
		float ang { 0 };

		Position operator+(const Position& first) const {
			return Position{ x + first.x, y + first.y, ang + first.ang };
		}

		Position& operator+=(const Position& first) {
			x += first.x;
			y += first.y;
			ang += first.ang;
			return *this;
		}
	};

	enum class Type {NONE, ARENA, ROBOT, WEAPON, BULLET, OBSTACLE};
}