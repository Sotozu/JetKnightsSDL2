#include "Obstacle.h"

// Generate obstacle with relative positioning
Obstacle::Obstacle(float relX, float relY, float relAng) {
	x = relX;
	y = relY;
	ang = relAng;
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
		hitbox.renderAll(posAbs.x, posAbs.y);
	}
}

void Obstacle::addDefaultHitbox() {
	Hitbox hitbox = Hitbox(100,100);
	hitboxes.push_back(hitbox);
}