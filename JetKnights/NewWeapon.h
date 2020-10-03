#pragma once
#include <iostream>
#include "GameObject.h"

class NewWeapon : public GameObject {
	private:
	int joyX;
	int joyY;

	int dirX;
	int dirY;

	int radius;
	const int JOYSTICK_DEAD_ZONE = 20000;
	bool inDeadCircle();
public:
	NewWeapon();
	NewWeapon(int x, int y, float angle, SDL_Renderer* renderer);
	NewWeapon(int x, int y, float angle, SDL_Renderer* renderer, LTexture* ltexture);



	void handleEvent( SDL_Event e );
	void update();
	float getAngle();
	int getJoyX();
	int getJoyY();


};

