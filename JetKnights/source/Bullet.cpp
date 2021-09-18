#include "Bullet.h"

Bullet::Bullet() : GameObject() {
	duration = 100;
	mSpeed = 0;
	damage = 1;
}


Bullet::Bullet(int m_x, int m_y, float angle, int speed, SDL_Renderer* renderer) : GameObject( m_x, m_y, angle, renderer) {
	duration = 100;
	mSpeed = speed;
	damage = 1;
}

Bullet::Bullet(int m_x, int m_y, float angle, int speed, SDL_Renderer* renderer, RelTexture* texture) : GameObject(m_x, m_y, angle, renderer, texture) {
	duration = 100;
	mSpeed = speed;
	damage = 1;
}

// Updates the position of the texture and the hitbox of the bullet
void Bullet::update(float timeStep) {
	posX = posX + getVelX() * timeStep;
	posY = posY + getVelY() * timeStep;
	for(auto &hitbox : hitboxes) {
		//hitbox.setPos(posX + hitboxOffsetX, posY + hitboxOffsetY);
	}
}


int Bullet::getVelX() {
	return  round(mSpeed * cos(ang * (M_PI / 180)));
}

int Bullet::getVelY() {
	return round(mSpeed * sin(ang * (M_PI / 180)));
}

int Bullet::getDamage() {
	return damage;
}

void Bullet::updateBorderCollision(int screenWidth, int screenHeight) {
	if (chkBorderCollision(screenWidth, screenHeight)) {
		isDead = true;
	}
}