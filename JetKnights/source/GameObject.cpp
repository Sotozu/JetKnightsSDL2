#include "GameObject.h"

GameObject::GameObject() {
	/*The 'hitbox' object requires a textures width and length
	No texture is passesd here. This will intialized  'hitbox' by its default constructor. 
	No need to explicitly set it here as C++ does that for us.
	*/

	gRenderer = NULL;
	texture = NULL;
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
	posX = x;
	posY = y;
	ang = angle;
	hitboxOffsetX = 0;
	hitboxOffsetY = 0;

}

GameObject::GameObject(int x, int y, float angle, SDL_Renderer* renderer, LTexture* ltexture) {
	gRenderer = renderer;
	texture = ltexture;
	posX = x;
	posY = y;
	setHitbox(); //Will initialize the private member variables 'hitbox'
	ang = angle;
	hitboxOffsetX = 0;
	hitboxOffsetY = 0;

}

void GameObject::render() {
	if (texture != NULL) {
		texture->render(posX, posY, NULL, gRenderer, ang);
	}
	hitbox.render();
}

void GameObject::setHitbox() {
	if (texture != NULL) {
		hitbox.setParameters(posX, posY, texture->getWidth(), texture->getHeight(), gRenderer);
	}
}

void GameObject::setHitbox(int h, int w, int offsetX=0, int offsetY=0) {
	hitboxOffsetX = offsetX;
	hitboxOffsetY = offsetY;
	hitbox = Hitbox(posX + offsetX, posY + offsetY, h, w, gRenderer);
}

void GameObject::setTexture(LTexture* tex) {
	texture = tex;
}

void GameObject::setPos(int x, int y, float angle=0.0) {
	posX = x;
	posY = y;
	ang = angle;
}

//update position
  //update hitbox position
  //upda
//check collision
//adjust state
  //update hitbox position
  //update texture position
//render