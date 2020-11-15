#pragma once
#include "GameObject.h"

//CONSTRUCTORS
GameObject::GameObject() {
	/*The 'hitbox' object requires a textures width and length
	No texture is passesd here. This will intialized  'hitbox' by its default constructor. 
	No need to explicitly set it here as C++ does that for us.
	*/

	gRenderer = NULL;
	posX = 0;
	posY = 0;
	ang = 0;
	hitboxOffsetX = 0;
	hitboxOffsetY = 0;
	isDead = false;
	isRelative = true;
	team = 0;

	relX = NULL;
	relY = NULL;

}


GameObject::GameObject(int x, int y, float angle, SDL_Renderer* renderer) {
	/*The 'hitbox' object requires a textures width and length
	No texture is passesd here. This will intialized  'hitbox' by its default constructor.
	No need to explicitly set it here as C++ does that for us.
	*/
	gRenderer = renderer;
	posX = x;
	posY = y;
	ang = angle;
	hitboxOffsetX = 0;
	hitboxOffsetY = 0;
	isDead = false;
	isRelative = true;
	team = 0;

	relX = NULL;
	relY = NULL;
}

GameObject::GameObject(int x, int y, float angle, SDL_Renderer* renderer, LTexture* texture) {
	gRenderer = renderer;
	textures.push_back(*texture);
	posX = x;
	posY = y;
	ang = angle;
	hitboxOffsetX = 0;
	hitboxOffsetY = 0;
	isDead = false;
	isRelative = true;
	team = 0;

	relX = NULL;
	relY = NULL;
}


void GameObject::render() {
	if (!isDead) {
		// make sure to pass by reference!!!
		for(auto &texture : textures) {
			texture.render(posX, posY, NULL, gRenderer, ang);
		}
		for(auto &hitbox : hitboxes) {
			hitbox.render();
		}
		SDL_Rect origin = { posX - 2, posY - 2, 5, 5 };
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
		SDL_RenderFillRect(gRenderer, &origin);
	}
}

void GameObject::addHitbox() {
	for(auto &texture : textures) {
		hitboxes.push_back(Hitbox(posX, posY, texture.getWidth(), texture.getHeight(), gRenderer));
	}
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

// are we using this? check to see if we can remove
Hitbox* GameObject::getHitbox() {
	for (auto hitbox : hitboxes) {
		return &hitbox;
	}
}

bool GameObject::chkBorderCollision(int screenWidth, int screenHeight) {
	for (auto hitbox : hitboxes) {
		if (hitbox.chkBorderCollisionX(screenWidth) || hitbox.chkBorderCollisionY(screenHeight)) {
			return true;
		}
	}
	return false;
}

void GameObject::setTeam(int a) {
	team = a;
}

void GameObject::setPosRelative(int x, int y, float angle) {
	setPos(x + posX, y + posY, ang + angle);
}

void GameObject::updateSelf() {
	std::cout << "self update has run" << std::endl;
	updateChildren();
}

void GameObject::updateChildren() {
	for (auto& variantObject : children) {
		std::visit([](auto& child) {child.updateSelf(); }, variantObject);
	}
}