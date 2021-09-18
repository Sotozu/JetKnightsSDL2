#include "Obstacle.h"

// Generate obstacle with relative positioning
Obstacle::Obstacle(float relX, float relY, float relAng) {
	m_x = relX;
	m_y = relY;
	m_ang = relAng;
}

void Obstacle::onEvent(SDL_Event e) {
	// Do nothing
}

void Obstacle::onUpdate(float timestep) {
	render();
}

jks::Type Obstacle::getType() {
	return jks::Type::OBSTACLE;
}

void Obstacle::renderHitbox() {
	jks::Position posAbs = getPositionAbsolute();

	for (Hitbox& hitbox : hitboxes) {
		hitbox.renderAll(posAbs.m_x, posAbs.m_y);
	}
}

void Obstacle::addDefaultHitbox() {
	Hitbox hitbox = Hitbox(100,100);
	addHitbox(hitbox);
}