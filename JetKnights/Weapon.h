#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include "LTexture.h"

class Texture;


class Weapon
{
public:
	//The dimensions of the weapon
	static const int DOT_WIDTH = 20;
	static const int DOT_HEIGHT = 20;

	//Maximum axis velocity of the weapon

	//Initializes the variables
	Weapon(LTexture* weaponTexture);


	//Shows the weapon on the screen
	void render(SDL_Renderer* gRenderer, double joystickAngle);


	int getxDir();
	int getyDir();

	int getPosX();
	int getPosY();

	void setPosX(int);
	void setPosY(int);

	void setVelX(int);
	void setVelY(int);

	void setDirY(int);
	void setDirX(int);

	void setOffSetX(int);
	void setOffSetY(int);

private:
	LTexture* weaponTexture;

	int off_setX;
	int off_setY;

	//The X and Y positions
	int mPosX, mPosY;

	//The velocity of the dot
	int mVelX, mVelY;

	//Normalized directions
	int xDir;
	int yDir;
};