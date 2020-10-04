#pragma once
#include "GameObject.h"
#include <iostream>
#include <cmath>
#include <SDL_gamecontroller.h>


class NewRobot : public GameObject{
public:
	//Constructors
	NewRobot();
	NewRobot(int x, int y, float angle, SDL_Renderer* renderer);
	NewRobot(int x, int y, float angle, SDL_Renderer* renderer, LTexture* ltexture);

	//Mutator
	void handleEvent(SDL_Event e);
	void update();


	//Accessor
	float getAngle();
	int getJoyX();
	int getJoyY();


private:
	static const int ROB_VEL = 1;
	static const int ROB_MAX_VEL = 10;
	int robotVelX;
	int robotVelY;
	int joyX;
	int joyY;

	int dirX;
	int dirY;

	int radius;
	const int JOYSTICK_DEAD_ZONE = 8000;

	bool inDeadCircle();
	bool chkCollision(int screenW, int screenH, Hitbox* b = NULL);


};

