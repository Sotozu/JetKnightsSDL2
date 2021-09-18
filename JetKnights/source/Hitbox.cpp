#include "Hitbox.h"

extern SDL_Renderer* gRenderer;

Hitbox::Hitbox() {
	m_x = 0;
	m_y = 0;
	m_w = 50;
	m_h = 50;
}

Hitbox::Hitbox(int width, int height) {
	m_x = 0;
	m_y = 0;
	m_w = width;
	m_h = height;
}

// Check if two hitboxes collide in absolute positions
bool Hitbox::chkCollision(Hitbox& b) {
	jks::Position thisPos  = parentObj->getPositionAbsolute();
	jks::Position otherPos = b.parentObj->getPositionAbsolute();

	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = m_x + thisPos.m_x - m_w / 2;
	rightA = leftA + m_w;
	topA = m_y + thisPos.m_y - m_h / 2;
	bottomA = topA + m_h;

	//Calculate the sides of rect B 
	leftB = b.m_x + otherPos.m_x - b.m_w / 2;
	rightB = leftB + b.m_w;
	topB = b.m_y + otherPos.m_y - b.m_h / 2;
	bottomB = topB + b.m_h;

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
	rect.m_x = static_cast<int>(m_x - m_w/2);
	rect.m_y = static_cast<int>(m_y - m_h/2);
	rect.m_w = static_cast<int>(m_w);
	rect.m_h = static_cast<int>(m_h);
	return &rect;
}

// Renders the hitbox at origin x,y
void Hitbox::renderAll(float posX, float posY) {

	renderOrigin(posX, posY);

	int pixX = static_cast<int>(posX);
	int pixY = static_cast<int>(posY);
	
	SDL_Rect* p_rect = getRect();
	p_rect->m_x += pixX;
	p_rect->m_y += pixY;

	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF); // Set color to red
	SDL_RenderDrawRect(gRenderer, p_rect);
}

// Renders the origin of the hitbox at the absolute coords
void Hitbox::renderOrigin(float m_x, float m_y) {
	// Render red origin
	int offset = 2;

	int pixX = static_cast<int>(m_x - offset);
	int pixY = static_cast<int>(m_y - offset);
	int pixW = offset * 2;
	int pixH = offset * 2;
	
	SDL_Rect origin = { pixX, pixY, pixW, pixH };

	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF); // Set color to red
	SDL_RenderFillRect(gRenderer, &origin);
}

void Hitbox::setParameters(int posX, int posY, int width, int height) {
	m_x = posX;
	m_y = posY;
	m_w = width;
	m_h = height;
}

bool Hitbox::chkBorderCollisionX(int screenWidth) {
	if ((m_x < 0) || (m_x + m_w > screenWidth)) {
		return true;
	}
	return false;
}

bool Hitbox::chkBorderCollisionY(int screenHeight) {
	if ((m_y < 0) || (m_y + m_h > screenHeight)) {
			return true;
	}
	return false;
}

int Hitbox::getPosX() {
	return m_x;
}

int Hitbox::getPosY() {
	return m_y;
}

int Hitbox::getWidth() {
	return m_w;
}

int Hitbox::getHeight() {
	return m_h;
}