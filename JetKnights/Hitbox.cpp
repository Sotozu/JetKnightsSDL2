#include "Hitbox.h"

Hitbox::Hitbox(int posX, int posY, int width, int height, SDL_Renderer* renderer) {
	gRenderer = renderer;
	x = posX;
	y = posY;
	w = width;
	h = height;
};

bool Hitbox::chkCollision(Hitbox b) {
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = x;
	rightA = x + w;
	topA = y;
	bottomA = y + h;

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB) {
		return false;
	}
	if (topA >= bottomB) {
		return false;
	}
	if (rightA <= leftB) {
		return false;
	}
	if (leftA >= rightB) {
		return false;
	}
	//If none of the sides from A are outside B
	return true;
}

int Hitbox::getWidth() {
	return w;
}

int Hitbox::getHeight() {
	return h;
}

SDL_Rect* Hitbox::getRect() {
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	return &rect;
}