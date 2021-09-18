#pragma once
#include "GameObject.h"

class Bullet : public GameObject {
public:

	//Constructors
	Bullet();
	Bullet(int m_x, int m_y, float angle, int speed, SDL_Renderer* renderer);
	Bullet(int m_x, int m_y, float angle, int speed, SDL_Renderer* renderer, RelTexture* texture);

	//Mutators
	void update(float);
	void updateBorderCollision(int, int);
	
	template<class T>
	void updateCollision(T* b, float timeStep) {
		if (chkCollision(b)) {
			isDead = true;
		}
	}
	
	//Accessors
	int getDamage();

private:
	int duration;
	int mSpeed;
	int damage;
	LTexture texture;
	int getVelX();
	int getVelY();
};

