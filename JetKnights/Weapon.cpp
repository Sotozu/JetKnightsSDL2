#pragma once
#include "Weapon.h"


Weapon::Weapon()
{
	//Initialize the offsets
	mPosX = 0;
	mPosY = 0;

	//Initialize the velocity
	mVelX = 0;
	mVelY = 0;

	//Normalized direction
	xDir = 0;
	yDir = 0;
}


void Weapon::render(SDL_Renderer* gRenderer, LTexture gWeaponTexture)
{
	//Show the arrow
	gWeaponTexture.render(mPosX, mPosY, NULL, gRenderer);
}

int Weapon::getxDir()
{
	return xDir;
}

int Weapon::getyDir()
{
	return yDir;
}



int Weapon::getPosX()
{
	return mPosX;
}

int Weapon::getPosY()
{
	return mPosY;
}



void Weapon::setPosX(int x)
{
	 mPosX = x;
}

void Weapon::setPosY(int y)
{
	mPosY = y;
}



void Weapon::setVelX(int x) {
	mVelX = x;
}
void Weapon::setVelY(int y) {
	mVelY = y;
}




void Weapon::setDirX(int x) {
	xDir = x;
}
void Weapon::setDirY(int y) {
	yDir = y;
}
