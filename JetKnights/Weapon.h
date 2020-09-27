#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include "LTexture.h"



class Weapon
{
public:
	//The dimensions of the weapon
	static const int DOT_WIDTH = 20;
	static const int DOT_HEIGHT = 20;

	//Maximum axis velocity of the weapon

	//Initializes the variables
	Weapon();


	//Shows the weapon on the screen
	void render(SDL_Renderer* gRenderer, LTexture gWeaponTexture);


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

private:

	//The X and Y offsets of the dot
	int mPosX, mPosY;

	//The velocity of the dot
	int mVelX, mVelY;

	//Normalized directions
	int xDir;
	int yDir;
};