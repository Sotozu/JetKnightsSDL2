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
	int getJoyX();
	int getJoyY();

	int getVelX();
	int getVelY();
	float getJoyAngle();

	void updateCollision(int screenW, int screenH, Hitbox* b = NULL);


private:
	const int MAX_SPEED = 8;
	static const int ROB_VEL = 1;
	static const int ROB_MAX_VEL = 10;
	static const int ROB_BOOST_SPEED = 16;
	int joyX;
	int joyY;

	int radius;
	int mSpeed;
	const int JOYSTICK_DEAD_ZONE = 8000;

	bool inDeadCircle();
};

