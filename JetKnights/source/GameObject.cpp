#include "GameObject.h"

GameObject::GameObject() {
	gRenderer = NULL;
	texture = NULL;
	hitbox = Hitbox();
	posX = 0;
	posY = 0;
	ang = 0;
	mSpeed = 0;
	hitboxOffsetX = 0;
	hitboxOffsetY = 0;
}

GameObject::GameObject(int x, int y, float angle, int speed, SDL_Renderer* renderer) {
	gRenderer = renderer;
	texture = NULL;
	hitbox = Hitbox();
	posX = x;
	posY = y;
	ang = angle;
	mSpeed = speed;
	hitboxOffsetX = 0;
	hitboxOffsetY = 0;
}

void GameObject::render() {
	texture->render(posX, posY, NULL, gRenderer, ang);
	hitbox.render();
}

void GameObject::update() {
	int newX, newY;
	newX = posX + getVelX();
	newY = posY + getVelY();
	//insert Check for collisions here
	posX = newX;
	posY = newY;
	hitbox.setPos(newX + hitboxOffsetX, newY + hitboxOffsetY);

}

void GameObject::setHitbox(int h, int w, int offsetX=0, int offsetY=0) {
	hitboxOffsetX = offsetX;
	hitboxOffsetY = offsetY;
	hitbox = Hitbox(posX + offsetX, posY + offsetY, h, w, gRenderer);
}

void GameObject::setTexture(LTexture* tex) {
	texture = tex;
}

int GameObject::getVelX() {
	return  mSpeed * cos(ang * (M_PI / 180));
}

int GameObject::getVelY() {
	return mSpeed * sin(ang * (M_PI / 180));
}

//update position
  //update hitbox position
  //upda
//check collision
//adjust state
  //update hitbox position
  //update texture position
//render