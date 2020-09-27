#pragma once
#include "Weapon.h"


Weapon::Weapon(LTexture* wepTex)
{
	weaponTexture = wepTex;

	//

	off_setX = 0;
	off_setY = 0;

	//Initialize x and y positions
	
	mPosX = 0;
	mPosY = 0;

	//Initialize the velocity
	mVelX = 0;
	mVelY = 0;

	//Normalized direction
	xDir = 0;
	yDir = 0;
}


void Weapon::render(SDL_Renderer* gRenderer, double joystickAngle)
{
	//Show the weapon
	//off set it to not be directly on the robot
	weaponTexture->render(mPosX + off_setX * cos(joystickAngle), mPosY + off_setY + off_setX * sin(joystickAngle), NULL, gRenderer, joystickAngle);

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


void Weapon::setOffSetX(int x) {
	off_setX = x;
}
void Weapon::setOffSetY(int y) {
	off_setY = y;
}
