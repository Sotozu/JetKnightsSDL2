#pragma once
#include "Robot.h"

int sign(int x) {
	if (x > 0) {
		return 1;
	}
	if (x < 0) {
		return -1;
	}
	if (x == 0) {
		return 0;
	}
}


Robot::Robot()
{
	//Initialize the offsets
	mPosX = 100;
	mPosY = 100;

	//Set collision box dimension
	mCollider.w = HITBOX_WIDTH;
	mCollider.h = HITBOX_HEIGHT;

	//Initialize the velocity
	mVelX = 0;
	mVelY = 0;

	//Normalized direction
	xDir = 0;
	yDir = 0;
	//Precise Directions
	joyX = 0;
	joyY = 0;
}

void Robot::handleEvent(SDL_Event& e, int JOYSTICK_DEAD_ZONE) {
	//If a key was pressed
	if (e.type == SDL_JOYAXISMOTION) {
		if (e.jaxis.which == 0) {
			//X axis motion
			if (e.jaxis.axis == 0) {
				joyX = e.jaxis.value;
				//Outside of dead zone
				if (abs(e.jaxis.value) > JOYSTICK_DEAD_ZONE) {
					
					mVelX = sign(joyX) * DOT_VEL;
				}
				else {
					mVelX = 0;
				}
			}
			//Y axis motion
			else if (e.jaxis.axis == 1) {
				joyY = e.jaxis.value;
				//Outside of dead zone
				if (abs(e.jaxis.value) > JOYSTICK_DEAD_ZONE) {
					
					mVelY = sign(joyY) * DOT_VEL;
				}
				else {
					mVelY = 0;
				}
			}
		}
	}
}

void Robot::move(int SCREEN_WIDTH, int SCREEN_HEIGHT, SDL_Rect b)
{

	//Move the dot left or right
	mPosX += mVelX;
	mCollider.x = mPosX;

	//If the dot went too far to the left or right
	if ((mPosX < 0) || (mPosX > SCREEN_WIDTH) || checkCollision(mCollider, b))
	{
		//Move back
		mPosX -= mVelX;
		mCollider.x = mPosX;
	}

	//Move the dot up or down
	mPosY += mVelY;
	mCollider.y = mPosY;

	//If the dot went too far up or down
	if ((mPosY < 0) || (mPosY > SCREEN_HEIGHT) || checkCollision(mCollider, b))
	{
		//Move back
		mPosY -= mVelY;
		mCollider.y = mPosY;
	}
}

void Robot::render(SDL_Renderer* gRenderer, LTexture gRobotTexture)
{
	//Show the arrow
	gRobotTexture.render(mPosX, mPosY, NULL, gRenderer);
}

int Robot::getxDir() {
	return xDir;
}

int Robot::getyDir() {
	return yDir;
}

int Robot::getJoyX() {
	return joyX;
}

int Robot::getJoyY() {
	return joyY;
}

int Robot::getPosX() {
	return mPosX;
}

int Robot::getPosY() {
	return mPosY;
}

float Robot::getAngle() {
	//Calculate angle
	double joyAngle = atan2((double)getJoyY(), (double)getJoyX()) * (180.0 / M_PI);
	std::cout << joyAngle << std::endl;
	//Correct angle
	if (getxDir() == 0 && getyDir() == 0) {
		//joyAngle = 0;
	}
	return joyAngle;
}

bool Robot::checkCollision(SDL_Rect a, SDL_Rect b) {
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB) {
		return false;
	}
	if (topA >= bottomB) {
		return false;
	}
	if (rightA <= leftB) {
		return false;
	}
	if (leftA >= rightB) {
		return false;
	}
	//If none of the sides from A are outside B
	return true;
}