#pragma once
#include <iostream>
#include "LTimer.h"

#include "GameObject.h"
#include "Bullet.h"



class NewWeapon : public GameObject {
public:
	//Constructors
	NewWeapon();
	NewWeapon(int x, int y, float angle, SDL_Renderer* renderer);
	NewWeapon(int x, int y, float angle, SDL_Renderer* renderer, RelTexture* texture);


	//Mutators
	void handleEvent(SDL_Event e);
	void update(float);
	void setAllParameters(int x, int y, float angle, SDL_Renderer* renderer, RelTexture* texture);
	//bool WeaponFiring(SDL_Event e);
	void setPlayer(int);
	void attemptToFire();

	//Accessors
	float getAngle();
	int getJoyX();
	int getJoyY();
	bool canFire();

	//Data
	int joyX;
	int joyY;
	bool isFiring;

private:
	int dirX;
	int dirY;

	int radius;
	int player;
	const int JOYSTICK_DEAD_ZONE = 20000;
	const int TRIGGER_DEAD_ZONE = 5000;
	bool inDeadCircle();

	LTimer stepTimer;
	int bulletInterval = 50;
};

