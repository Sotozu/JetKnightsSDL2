#pragma once

#include "Constants.h"

#include "Hitbox.h"
#include "RelTexture.h"

#include <SDL.h>

#include <iostream>
#include <list>

class Hitbox;

class IGameObject {

public:
	//Constructors
	IGameObject() {};

	//Mutators
	virtual void setDefaultHitbox() {};
	virtual void setTexture(RelTexture* tex) {};
	virtual void setTeam(int team) {};

	virtual void setPosition(float m_x, float m_y, float angle) {};
	virtual void setPositionRelative(float m_x, float m_y, float angle) {};

	virtual void handleUpdate(float timestep);
	virtual void onUpdate(float timestep) {};
	virtual void handleEvent(SDL_Event e);
	virtual void onEvent(SDL_Event e) {};

	virtual void addChild(IGameObject* childObj);
	virtual void addHitbox(Hitbox& hitbox);

	//Accessors
	//virtual jks::Position getPositionRelative() {}; // Get relative Position
	virtual jks::Position getPositionAbsolute(); // Get absolute Position
	virtual Hitbox& getHitbox();
	virtual std::list<Hitbox>& getHitboxes();
	//virtual RelTexture* getTexture() {};
	virtual jks::Type getType();

	//Pocesses
	virtual void render();
	virtual void renderOrigin(float m_x, float m_y);
	virtual void renderHitbox() {};
	//virtual void renderTextures();

	//virtual bool chkCollision(IGameObject* obj) {};
	virtual bool isColliding(IGameObject* otherObj);
	virtual std::list<IGameObject*> getAllObjects();
	virtual std::list<IGameObject*> getAllChildren();

	//Data
	IGameObject * parent;
	std::list<IGameObject*> childs;

	bool isDead{false};
	bool isActive{ true };
	int team;

protected:
	float m_x;
	float m_y;
	float m_ang;

	std::list<RelTexture> textures;
	std::list<Hitbox> hitboxes;
};