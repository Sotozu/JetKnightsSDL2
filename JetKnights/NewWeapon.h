#pragma once
#include <iostream>
#include "GameObject.h"
#include "Bullet.h"


class NewWeapon : public GameObject {
public:
	int joyX;
	int joyY;
	//Constructors
	NewWeapon();
	NewWeapon(int x, int y, float angle, SDL_Renderer* renderer);
	NewWeapon(int x, int y, float angle, SDL_Renderer* renderer, LTexture* ltexture);


	//Mutators
	void update();
	void setAllParameters(int x, int y, float angle, SDL_Renderer* renderer, LTexture* ltexture);
	bool WeaponFiring(SDL_Event e);

	//Accessors
	float getAngle();
	int getJoyX();
	int getJoyY();

	//Proccesses
	void handleEvent( SDL_Event e );

private:


	int dirX;
	int dirY;
	             
	int muzzleX;
	int muzzleY;

	int radius;
	const int JOYSTICK_DEAD_ZONE = 20000;
	const int TRIGGER_DEAD_ZONE = 4000;
	bool inDeadCircle();
	
};

