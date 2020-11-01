#include "StatusBar.h"

StatusBar::StatusBar() {
	renderer = NULL;
	status = NULL;
	x = 0;
	y = 0;
	status_rect = { 0, 0, WIDTH, HEIGHT };
	casing_rect = { 0, 0, WIDTH, HEIGHT };
	max_bar = 1;

	val = 0;
}

// Warning: This pointer based data access is prone to garbage data once the object in question is deleted
StatusBar::StatusBar(int x, int y, int* st, SDL_Renderer* renderer){
	this->status = st;
	this->renderer = renderer;
	this->x = x;
	this->y = y;
	status_rect = { x, y, direction * WIDTH, HEIGHT };
	casing_rect = { x, y, direction * WIDTH, HEIGHT };
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

	status_rect.w = direction * val;
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
	return status_rect.x;
}

int StatusBar::getY() {
	return status_rect.y;
}

// Reverse the direction of the bar
void StatusBar::reverse() {
	if (direction == 1) {
		direction = -1;
	}
	else {
		direction = 1;
	}
	casing_rect = { x, y, direction * WIDTH, HEIGHT };
}