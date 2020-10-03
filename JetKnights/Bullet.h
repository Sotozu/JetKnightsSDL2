#pragma once
#include "GameObject.h"

class Bullet : public GameObject {
public:

	//Constructors
	Bullet();
	Bullet(int x, int y, float angle, int speed, SDL_Renderer* renderer);
	Bullet(int x, int y, float angle, int speed, SDL_Renderer* renderer, LTexture* ltexture);

	//Accessor


	//Processes
	void update();
	void updateAll();
	bool chkCollision(Hitbox b);



private:
	int duration;
	int mSpeed;
	LTexture texture;
	int getVelX();
	int getVelY();
};

