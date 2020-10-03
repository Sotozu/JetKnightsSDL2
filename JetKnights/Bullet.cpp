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
	if (hitbox != NULL) {
		hitbox->setPos(posX + hitboxOffsetX, posY + hitboxOffsetY);
	}
}

void Bullet::updateAll() {

}

bool Bullet::chkCollision( int screenW, int screenH, Hitbox* b ) {
	if (hitbox != NULL) {
		if ((hitbox->x < 0) || (hitbox->x + hitbox->w > screenW) || (hitbox->y < 0) || (hitbox->y + hitbox->h > screenH)) {
			return true;
		}
		else if (b != NULL) {
			return hitbox->chkCollision(b);
		}
	}
	return false;
}

int Bullet::getVelX() {
	return  mSpeed * cos(ang * (M_PI / 180));
}

int Bullet::getVelY() {
	return mSpeed * sin(ang * (M_PI / 180));
}