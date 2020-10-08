#pragma once
#include "GameObject.h"

class Bullet : public GameObject {
public:

	//Constructors
	Bullet();
	Bullet(int x, int y, float angle, int speed, SDL_Renderer* renderer);
	Bullet(int x, int y, float angle, int speed, SDL_Renderer* renderer, LTexture* ltexture);

	//Mutators
	template<class T>
	void updateCollision(T* b) {
		if (chkCollision(b)) {
			isDead = true;
		}
	}
	void updateBorderCollision(int, int);
	
	//Accessor
	int getDamage();

	//Processes
	void update();

private:
	int duration;
	int mSpeed;
	int damage;
	LTexture texture;
	int getVelX();
	int getVelY();
};

