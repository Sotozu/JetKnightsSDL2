#pragma once
#include <iostream>
#include "GameObject.h"

class NewWeapon : public GameObject {
public:
	NewWeapon();
	NewWeapon(int x, int y, float angle, SDL_Renderer* renderer);
	void handleEvent( SDL_Event e );
	void update();
	float getAngle();
	int getJoyX();
	int getJoyY();
private:
	int joyX;
	int joyY;
	int dirX;
	int dirY;
	const int JOYSTICK_DEAD_ZONE = 20000;
	bool inDeadCircle();
};

