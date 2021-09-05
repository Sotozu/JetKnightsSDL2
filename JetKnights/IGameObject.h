#pragma once

#include "Constants.h"

#include "Hitbox.h"
#include "RelTexture.h"

#include <SDL.h>

#include <iostream>
#include <list>


class IGameObject {

public:
	//Constructors
	IGameObject() {};

	//Mutators
	virtual void setDefaultHitbox() {};
	virtual void setTexture(RelTexture* tex) {};
	virtual void setTeam(int team) {};

	virtual void setPosition(float x, float y, float angle) {};
	virtual void setPositionRelative(float x, float y, float angle) {};

	virtual void update(float timestep) {};
	virtual void handleEvent(SDL_Event e) {};

	virtual void addChild(IGameObject* childObj);

	//Accessors
	virtual jks::Position getPosition() {};
	virtual Hitbox* getHitbox() {};
	virtual RelTexture* getTexture() {};

	//Pocesses
	virtual void render() {};
	virtual void renderTextures() {};
	virtual void renderHitboxes() {};

	virtual bool chkCollision(IGameObject* obj) {};

	//Data
	IGameObject * parent;
	std::list<IGameObject*> childs;

	bool isDead;
	bool isActive;
	int team;

protected:
	float x;
	float y;
	float ang;

	std::list<RelTexture> textures;
	std::list<Hitbox> hitboxes;

	int hitboxOffsetX = 0;
	int hitboxOffsetY = 0;
};