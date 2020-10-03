#pragma once
#include <iostream>
#include "GameObject.h"

class NewWeapon : public GameObject {
	private:
;

	int dirX;
	int dirY;

	int radius;
	const int JOYSTICK_DEAD_ZONE = 20000;
	bool inDeadCircle();
public:
	int joyX;
	int joyY
	//Constructors
	NewWeapon();
	NewWeapon(int x, int y, float angle, SDL_Renderer* renderer);
	NewWeapon(int x, int y, float angle, SDL_Renderer* renderer, LTexture* ltexture);


	//Mutators
	void update();
	void setAllParameters(int x, int y, float angle, SDL_Renderer* renderer, LTexture* ltexture);

	//Accessors
	float getAngle();
	int getJoyX();
	int getJoyY();

	//Proccesses
	void handleEvent( SDL_Event e );



};

