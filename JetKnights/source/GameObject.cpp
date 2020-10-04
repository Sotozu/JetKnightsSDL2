#include "GameObject.h"

//CONSTRUCTORS
GameObject::GameObject() {
	/*The 'hitbox' object requires a textures width and length
	No texture is passesd here. This will intialized  'hitbox' by its default constructor. 
	No need to explicitly set it here as C++ does that for us.
	*/

	gRenderer = NULL;
	texture = NULL;
	hitbox = NULL;
	posX = 0;
	posY = 0;
	ang = 0;
	hitboxOffsetX = 0;
	hitboxOffsetY = 0;

}


GameObject::GameObject(int x, int y, float angle, SDL_Renderer* renderer) {
	/*The 'hitbox' object requires a textures width and length
	No texture is passesd here. This will intialized  'hitbox' by its default constructor.
	No need to explicitly set it here as C++ does that for us.
	*/
	gRenderer = renderer;
	texture = NULL;
	hitbox = NULL;
	posX = x;
	posY = y;
	ang = angle;
	hitboxOffsetX = 0;
	hitboxOffsetY = 0;

}

GameObject::GameObject(int x, int y, float angle, SDL_Renderer* renderer, LTexture* ltexture) {
	gRenderer = renderer;
	texture = ltexture;
	hitbox = NULL;
	posX = x;
	posY = y;
	ang = angle;
	hitboxOffsetX = 0;
	hitboxOffsetY = 0;
}


void GameObject::render() {
	if (texture != NULL) {
		texture->render(posX, posY, NULL, gRenderer, ang);
	}
	if (hitbox != NULL) {
		hitbox->render();
	}
}

void GameObject::setHitbox() {
	if (texture != NULL) {
		hitbox = new Hitbox(posX, posY, texture->getWidth(), texture->getHeight(), gRenderer);
	}
}

void GameObject::setHitbox(int h, int w, int offsetX=0, int offsetY=0) {
	hitboxOffsetX = offsetX;
	hitboxOffsetY = offsetY;
	hitbox = new Hitbox(posX + offsetX, posY + offsetY, h, w, gRenderer);
}

void GameObject::setTexture(LTexture* tex) {
	texture = tex;
}

void GameObject::setPos(int x, int y, float angle=0.0) {
	posX = x;
	posY = y;
	ang = angle;
}

int  GameObject::getPosX() {
	return posX;
}
int  GameObject::getPosY() {
	return posY;
}
float  GameObject::getAng() {
	return ang;
}
Hitbox* GameObject::getHitbox() {
	return hitbox;
}

