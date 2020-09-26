


#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>


class Robot
{
public:
	//The dimensions of the robot
	static const int DOT_WIDTH = 20;
	static const int DOT_HEIGHT = 20;

	//Maximum axis velocity of the robot
	static const int DOT_VEL = 1;

	//Initializes the variables
	Robot();

	//Takes key presses and adjusts the robot's velocity
	void handleEvent(SDL_Event& e);

	//Moves the dot
	void move();

	//Shows the robot on the screen
	void render();


	int getxDir();
	int getyDir();

	int getPosX();
	int getPosY();

private:
	//The X and Y offsets of the dot
	int mPosX, mPosY;

	//The velocity of the dot
	int mVelX, mVelY;

	//Normalized directions
	int xDir;
	int yDir;
};