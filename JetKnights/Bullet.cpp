#include "Bullet.h"

Bullet::Bullet() {
	GameObject();
	duration = 100;
	mSpeed = 0;
}

Bullet::Bullet(int x, int y, float angle, int speed, SDL_Renderer* renderer) {
	posX = x;
	posY = y;
	ang = angle;
	gRenderer = renderer;
	duration = 100;
	mSpeed = speed;
}

void Bullet::update() {
	oldX = posX;
	oldY = posY;
	posX = posX + getVelX();
	posY = posY + getVelY();
	hitbox.setPos(posX + hitboxOffsetX, posY + hitboxOffsetY);
}

void Bullet::updateAll() {

}

bool Bullet::chkCollision( Hitbox b ) {
	return hitbox.chkCollision(b);
}

int Bullet::getVelX() {
	return  mSpeed * cos(ang * (M_PI / 180));
}

int Bullet::getVelY() {
	return mSpeed * sin(ang * (M_PI / 180));
}