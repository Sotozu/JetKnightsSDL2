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
	void handleEvent(SDL_Event e);
	void update();
	bool chkCollision(int screenW, int screenH, Hitbox* b = NULL);



private:
	int duration;
	int mSpeed;
	LTexture texture;
	int getVelX();
	int getVelY();
};

