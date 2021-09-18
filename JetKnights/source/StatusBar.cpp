#include "StatusBar.h"

StatusBar::StatusBar() {
	renderer = NULL;
	status = NULL;
	m_x = 0;
	m_y = 0;
	status_rect = { 0, 0, WIDTH, HEIGHT };
	casing_rect = { 0, 0, WIDTH, HEIGHT };
	max_bar = 1;

	val = 0;
}

// Warning: This pointer based data access is prone to garbage data once the object in question is deleted
// It is a dirty way to get relative objects, create nested objects instead.
StatusBar::StatusBar(int m_x, int m_y, int* st, SDL_Renderer* renderer){
	this->status = st;
	this->renderer = renderer;
	this->m_x = m_x;
	this->m_y = m_y;
	status_rect = { m_x, m_y, direction * WIDTH, HEIGHT };
	casing_rect = { m_x, m_y, direction * WIDTH, HEIGHT };
	max_bar = *st;

	val = *st;
}

void StatusBar::update() {
	int temp_val = 300 * (*status / 100.0);
	if (temp_val > 0) {
		val = temp_val;
	}
	else {
		val = 0;
	}

	status_rect.m_w = direction * val;
}

void StatusBar::render() {
	SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(renderer, &status_rect);
	
	if (show_casing) {
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderDrawRect(renderer, &casing_rect);
	}
}

int StatusBar::getX() {
	return status_rect.m_x;
}

int StatusBar::getY() {
	return status_rect.m_y;
}

// Reverse the direction of the bar
void StatusBar::reverse() {
	if (direction == 1) {
		direction = -1;
	}
	else {
		direction = 1;
	}
	casing_rect = { m_x, m_y, direction * WIDTH, HEIGHT };
}