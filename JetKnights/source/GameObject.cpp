#pragma once
#include "GameObject.h"

//CONSTRUCTORS
GameObject::GameObject() {
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
	isActive = true;
	isRelative = true;
	team = 0;
}


GameObject::GameObject(int m_x, int m_y, float angle, SDL_Renderer* renderer) {
	gRenderer = renderer;
	oriX = 0;
	oriY = 0;
	relX = m_x;
	relY = m_y;
	posX = m_x;
	posY = m_y;
	ang = angle;
	hitboxOffsetX = 0;
	hitboxOffsetY = 0;
	isDead = false;
	isActive = true;
	isRelative = true;
	team = 0;
}

GameObject::GameObject(int m_x, int m_y, float angle, SDL_Renderer* renderer, RelTexture* texture) {
	gRenderer = renderer;
	textures.push_back(*texture);
	oriX = 0;
	oriY = 0;
	relX = m_x;
	relY = m_y;
	posX = m_x;
	posY = m_y;
	ang = angle;
	hitboxOffsetX = 0;
	hitboxOffsetY = 0;
	isDead = false;
	isActive = true;
	isRelative = true;
	team = 0;
}


void GameObject::render() {
	if (!isDead && isActive) {
		// make sure to pass by reference for all these!!!
		renderTextures();
		renderHitboxes();
		// Render Origin
		SDL_Rect origin = { posX - 2, posY - 2, 5, 5 };
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
		SDL_RenderFillRect(gRenderer, &origin);

		// Render Children
		for (auto& variantObject : children) {
			std::visit([&](auto& child) {
				child.render();
			}, variantObject);
		}
	}
}

void GameObject::renderHitboxes() {
	for (auto& hitbox : hitboxes) {
		//hitbox.render();
	}
}

void GameObject::renderTextures() {
	for (auto& texture : textures) {
		texture.render(posX, posY, ang);

		// These are all for rendering relations
		SDL_Rect textureOrigin = { posX + texture.m_x - 2, posY + texture.m_y - 2, 5, 5 };
		SDL_Rect textureBounds = { posX + texture.m_x, posY + texture.m_y, texture.getWidth(), texture.getHeight() };
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
		SDL_RenderFillRect(gRenderer, &textureOrigin);
		SDL_RenderDrawRect(gRenderer, &textureBounds);
		SDL_RenderDrawLine(gRenderer, posX, posY, posX + texture.m_x, posY + texture.m_y);
	}
}

// Adds default hitbox to object
void GameObject::addHitbox() {
	for(auto &texture : textures) {
		Hitbox hitbox = Hitbox(texture.getWidth(), texture.getHeight());
		hitboxes.push_back(hitbox);
	}
}

void GameObject::updatePos() {
	posX = oriX + relX;
	posY = oriY + relY;
	for (auto& hitbox : hitboxes) {
		//hitbox.setPos(posX, posY);
	}
}

void GameObject::setOrigin(float m_x, float m_y) {
	oriX = m_x;
	oriY = m_y;
	updatePos();
}

void GameObject::setPos(int m_x, int m_y, float angle=0.0) {
	relX = m_x;
	relY = m_y;
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
// Returns first hitbox in the list
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

void GameObject::setPosRelative(int m_x, int m_y, float angle) {
	setPos(m_x + posX, m_y + posY, ang + angle);
}

void GameObject::update(float timestep) {
	if (isActive)
		updateChildren(timestep);
}

void GameObject::handleEvent(SDL_Event e) {
	// Do nothing
	if (isActive)
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
		}, variantObject);

	}
}