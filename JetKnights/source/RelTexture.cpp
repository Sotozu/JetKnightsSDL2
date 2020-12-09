#include "RelTexture.h"

RelTexture::RelTexture() {
	x = 0;
	y = 0;
	ang = 0;
	texture = LTexture();
	renderer = NULL;
}

RelTexture::RelTexture(float x, float y, float ang, LTexture* texture, SDL_Renderer* renderer) {
	this->x = x;
	this->y = y;
	this->ang = ang;
	this->texture = *texture;
	this->renderer = renderer;
}

void RelTexture::render(float x, float y, float ang) {
	int posX = this->x + x;
	int posY = this->y + y;
	double posAng = this->ang + ang;
	texture.render(posX, posY, NULL, renderer, posAng);
}

int RelTexture::getWidth() {
	return texture.getWidth();
}

int RelTexture::getHeight() {
	return texture.getHeight();
}