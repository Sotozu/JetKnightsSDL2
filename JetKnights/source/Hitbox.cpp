#include "Hitbox.h"

Hitbox::Hitbox() {
	gRenderer = NULL;
	x = 0;
	y = 0;
	w = 0;
	h = 0;

	relX = 0;
	relY = 0;
}

Hitbox::Hitbox(int posX, int posY, int width, int height, SDL_Renderer* renderer) {
	gRenderer = renderer;
	x = posX;
	y = posY;
	w = width;
	h = height;
}

bool Hitbox::chkCollision(Hitbox* b) {
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
	leftB = b->x;
	rightB = b->x + b->w;
	topB = b->y;
	bottomB = b->y + b->h;

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
	// If none of the sides from A are outside B
	return true;
}

int Hitbox::getWidth() {
	return w;
}

int Hitbox::getHeight() {
	return h;
}

void Hitbox::setPos(int posX, int posY) {
	x = posX;
	y = posY;
}
void Hitbox::setPosX(int posX) {
	x = posX;
}
void Hitbox::setPosY(int posY) {
	y = posY;
}

SDL_Rect* Hitbox::getRect() {
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	return &rect;
}

void Hitbox::render() {
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderDrawRect(gRenderer, getRect());
}

void Hitbox::setParameters(int posX, int posY, int width, int height, SDL_Renderer* renderer) {
	x = posX;
	y = posY;
	w = width;
	h = height;
	gRenderer = renderer;
}

bool Hitbox::chkBorderCollisionX(int screenWidth) {
	if ((x < 0) || (x + w > screenWidth)) {
		return true;
	}
	return false;
}

bool Hitbox::chkBorderCollisionY(int screenHeight) {
	if ((y < 0) || (y + h > screenHeight)) {
			return true;
	}
	return false;
}

int Hitbox::getPosX() {
	return x;
}
int Hitbox::getPosY() {
	return y;
}