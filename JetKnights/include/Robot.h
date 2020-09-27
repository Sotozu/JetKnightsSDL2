


#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include "LTexture.h"


class Robot
{
public:
	//The dimensions of the robot
	static const int HITBOX_WIDTH = 32;
	static const int HITBOX_HEIGHT = 32;

	//Maximum axis velocity of the robot
	static const int DOT_VEL = 3;

	//Initializes the variables
	Robot();

	//Takes key presses and adjusts the robot's velocity
	void handleEvent(SDL_Event& e, int JOYSTICK_DEAD_ZONE);

	//Moves the dot
	void move(int SCREEN_WIDTH, int SCREEN_HEIGHT);

	//Shows the robot on the screen
	void render(SDL_Renderer* gRenderer, LTexture gRobotTexture);


	int getxDir();
	int getyDir();

	int getJoyX();
	int getJoyY();

	int getPosX();
	int getPosY();

	float getAngle();

private:
	//The X and Y offsets of the dot
	int mPosX, mPosY;

	//The velocity of the dot
	int mVelX, mVelY;

	//Normalized directions
	int xDir;
	int yDir;
	
	//Precise Directions
	int joyX;
	int joyY;

	//Dot's collision box
	SDL_Rect mCollider;
};