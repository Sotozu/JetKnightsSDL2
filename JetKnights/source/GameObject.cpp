#pragma once
#include "GameObject.h"

//CONSTRUCTORS
GameObject::GameObject() {
	/*The 'hitbox' object requires a textures width and length
	No texture is passesd here. This will intialized  'hitbox' by its default constructor. 
	No need to explicitly set it here as C++ does that for us.
	*/

	gRenderer = NULL;
	oriX = 0;
	oriY = 0;
	relX = 0;
	relY = 0;
	posX = 0;
	posY = 0;
	ang = 0;
	hitboxOffsetX = 0;
	hitboxOffsetY = 0;
	isDead = false;
	isRelative = true;
	team = 0;

	//relXp = NULL;
	//relYp = NULL;

}


GameObject::GameObject(int x, int y, float angle, SDL_Renderer* renderer) {
	/*The 'hitbox' object requires a textures width and length
	No texture is passesd here. This will intialized  'hitbox' by its default constructor.
	No need to explicitly set it here as C++ does that for us.
	*/
	gRenderer = renderer;
	oriX = 0;
	oriY = 0;
	relX = x;
	relY = y;
	posX = x;
	posY = y;
	ang = angle;
	hitboxOffsetX = 0;
	hitboxOffsetY = 0;
	isDead = false;
	isRelative = true;
	team = 0;

	//relXp = NULL;
	//relYp = NULL;
}

GameObject::GameObject(int x, int y, float angle, SDL_Renderer* renderer, RelTexture* texture) {
	gRenderer = renderer;
	textures.push_back(*texture);
	oriX = 0;
	oriY = 0;
	relX = x;
	relY = y;
	posX = x;
	posY = y;
	ang = angle;
	hitboxOffsetX = 0;
	hitboxOffsetY = 0;
	isDead = false;
	isRelative = true;
	team = 0;

	//relXp = NULL;
	//relYp = NULL;
}


void GameObject::render() {
	if (!isDead) {
		// make sure to pass by reference for all these!!!
		renderTextures();
		renderHitboxes();
		// Render Origin
		SDL_Rect origin = { posX - 2, posY - 2, 5, 5 };
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
		SDL_RenderFillRect(gRenderer, &origin);

		// Render Children
		for (auto& variantObject : children) {
			std::visit([](auto& child) {
				child.render();
			}, variantObject);
		}
	}
}

void GameObject::renderHitboxes() {
	for (auto& hitbox : hitboxes) {
		hitbox.render();
	}
}

void GameObject::renderTextures() {
	for (auto& texture : textures) {
		texture.render(posX, posY, ang);

		// These are all for viewing relations
		SDL_Rect textureOrigin = { posX + texture.x - 2, posY + texture.y - 2, 5, 5 };
		SDL_Rect textureBounds = { posX + texture.x, posY + texture.y, texture.getWidth(), texture.getHeight() };
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
		SDL_RenderFillRect(gRenderer, &textureOrigin);
		SDL_RenderDrawRect(gRenderer, &textureBounds);
		SDL_RenderDrawLine(gRenderer, posX, posY, posX + texture.x, posY + texture.y);
	}
}

// Adds default hitbox to object
void GameObject::addHitbox() {
	for(auto &texture : textures) {
		hitboxes.push_back(Hitbox(posX + texture.x, posY + texture.y, texture.getWidth(), texture.getHeight(), gRenderer));
	}
}

void GameObject::updatePos() {
	posX = oriX + relX;
	posY = oriY + relY;
	for (auto& hitbox : hitboxes) {
		hitbox.setPos(posX, posY);
	}
}

void GameObject::setOrigin(float x, float y) {
	oriX = x;
	oriY = y;
	updatePos();
}

void GameObject::setPos(int x, int y, float angle=0.0) {
	relX = x;
	relY = y;
	ang = angle;
	updatePos();
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
// only returns first hitbox atm
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
	for (auto& varObj : children) {
		std::visit([&](auto& child) {
			child.setTeam(a);
		}, varObj);
	}
}

void GameObject::setPosRelative(int x, int y, float angle) {
	setPos(x + posX, y + posY, ang + angle);
}

void GameObject::update(float timestep) {
	//std::cout << "self update has run" << std::endl;
	updateChildren(timestep);
}

void GameObject::handleEvent(SDL_Event e) {
	// Do nothing
	passOnEvent(e);
}

void GameObject::passOnEvent(SDL_Event e) {
	for (auto& variantObject : children) {
		std::visit([&](auto& child) {
			child.handleEvent(e);
		}, variantObject);

	}
}

void GameObject::updateChildren(float timestep) {
	for (auto& variantObject : children) {
		std::visit([&](auto& child) {
			child.setOrigin(getPosX(), getPosY());
			child.update(timestep);
		}, variantObject);

	}
}