#include "Arena.h"

Arena::Arena() {
	m_x = 0;
	m_y = 0;
	m_ang = 0;
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