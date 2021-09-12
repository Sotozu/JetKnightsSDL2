#include "Arena.h"

Arena::Arena() {
	x = 0;
	y = 0;
	ang = 0;
}

void Arena::onEvent(SDL_Event e) {
	// Do nothing
}

void Arena::onUpdate(float timestep) {
	render();
}

jks::Type Arena::getType() {
	return jks::Type::ARENA;
}