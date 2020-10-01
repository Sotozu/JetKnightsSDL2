#include "Bullet.h"

Bullet::Bullet() {
	duration = 100;
	mSpeed = 0;
}


Bullet::Bullet(int x, int y, float angle, int speed, SDL_Renderer* renderer) : GameObject( x, y, angle, renderer) {
	duration = 100;
	mSpeed = speed;
}

Bullet::Bullet(int x, int y, float angle, int speed, SDL_Renderer* renderer, LTexture* ltexture) : GameObject(x, y, angle, renderer, ltexture) {
	duration = 100;
	mSpeed = speed;
}


/*
Updates the position of the texture and the hitbox of the bullet
*/
void Bullet::update() {
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