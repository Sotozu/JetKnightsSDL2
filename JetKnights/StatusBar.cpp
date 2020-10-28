#include "StatusBar.h"

StatusBar::StatusBar() {
	renderer = NULL;
	status = NULL;
	rect = { 0, 0, WIDTH, HEIGHT };
	max_bar = 1;
	x = 0;
	y = 0;
	val = 0;
}

StatusBar::StatusBar(int x, int y, int* st, SDL_Renderer* renderer){
	this->status = st;
	this->renderer = renderer;
	rect = { x, y, WIDTH, HEIGHT };
	max_bar = *st;
	this->x = x;
	this->y = y;
	val = *st;
	//std::cout << *status << std::endl;
}

void StatusBar::update() {
	rect.w = 300 * (*status / 100.0);
}

void StatusBar::render() {
	SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(renderer, &rect);
}

int StatusBar::getX() {
	return rect.x;
}

int StatusBar::getY() {
	return rect.y;
}