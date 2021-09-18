#pragma once

namespace jks {

	struct Position {
		float m_x   { 0 };
		float m_y   { 0 };
		float ang { 0 };

		Position operator+(const Position& first) const {
			return Position{ m_x + first.m_x, m_y + first.m_y, ang + first.ang };
		}

		Position& operator+=(const Position& first) {
			m_x += first.m_x;
			m_y += first.m_y;
			ang += first.ang;
			return *this;
		}
	};

	enum class Type {NONE, ARENA, ROBOT, WEAPON, BULLET, OBSTACLE};
}