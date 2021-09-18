#include "RelTexture.h"

RelTexture::RelTexture() {
	m_x = 0;
	m_y = 0;
	ang = 0;
	texture = LTexture();
	renderer = NULL;
}

RelTexture::RelTexture(float m_x, float m_y, float ang, LTexture* texture, SDL_Renderer* renderer) {
	this->m_x = m_x;
	this->m_y = m_y;
	this->ang = ang;
	this->texture = *texture;
	this->renderer = renderer;
}

void RelTexture::render(float m_x, float m_y, float ang) {
	int posX = this->m_x + m_x;
	int posY = this->m_y + m_y;
	double posAng = this->ang + ang;
	texture.render(posX, posY, NULL, renderer, posAng);
}

int RelTexture::getWidth() {
	return texture.getWidth();
}

int RelTexture::getHeight() {
	return texture.getHeight();
}