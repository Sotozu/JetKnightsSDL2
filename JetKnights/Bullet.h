#pragma once
#include "GameObject.h"

class Bullet : public GameObject {
public:
	Bullet();
	Bullet(int x, int y, float angle, int speed, SDL_Renderer* renderer);
	Bullet(int x, int y, float angle, int speed, SDL_Renderer* renderer, LTexture* ltexture);

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

