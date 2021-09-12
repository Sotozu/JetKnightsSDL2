#include "Hitbox.h"

extern SDL_Renderer* gRenderer;

Hitbox::Hitbox() {
	x = 0;
	y = 0;
	w = 50;
	h = 50;
}

Hitbox::Hitbox(int width, int height) {
	x = 0;
	y = 0;
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

SDL_Rect* Hitbox::getRect() {
	SDL_Rect rect;
	rect.x = static_cast<int>(x - w/2);
	rect.y = static_cast<int>(y - h/2);
	rect.w = static_cast<int>(w);
	rect.h = static_cast<int>(h);
	return &rect;
}

// Renders the hitbox at origin x,y
void Hitbox::renderAll(float posX, float posY) {

	renderOrigin(posX, posY);

	int pixX = static_cast<int>(posX);
	int pixY = static_cast<int>(posY);
	
	SDL_Rect* p_rect = getRect();
	p_rect->x += pixX;
	p_rect->y += pixY;

	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF); // Set color to red
	SDL_RenderDrawRect(gRenderer, p_rect);
}

// Renders the origin of the hitbox at the absolute coords
void Hitbox::renderOrigin(float x, float y) {
	// Render red origin
	int offset = 2;

	int pixX = static_cast<int>(x - offset);
	int pixY = static_cast<int>(y - offset);
	int pixW = offset * 2;
	int pixH = offset * 2;
	
	SDL_Rect origin = { pixX, pixY, pixW, pixH };

	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF); // Set color to red
	SDL_RenderFillRect(gRenderer, &origin);
}

void Hitbox::setParameters(int posX, int posY, int width, int height) {
	x = posX;
	y = posY;
	w = width;
	h = height;
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

int Hitbox::getWidth() {
	return w;
}

int Hitbox::getHeight() {
	return h;
}