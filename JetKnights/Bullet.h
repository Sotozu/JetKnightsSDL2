#pragma once
#include "GameObject.h"

class Bullet : public GameObject {
public:
	Bullet();
	Bullet(int x, int y, float angle, int speed, SDL_Renderer* renderer);

	void update();
	void updateAll();
	bool chkCollision(Hitbox b);

private:
	bool is_dead;
	int oldX, oldY;
	int duration;
	int speed;
	int getVelX();
	int getVelY();
};

