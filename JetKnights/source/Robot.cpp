#pragma once
#include "Robot.h"


Robot::Robot()
{
	//Initialize the offsets
	mPosX = 100;
	mPosY = 100;

	//Initialize the velocity
	mVelX = 0;
	mVelY = 0;

	//Normalized direction
	xDir = 0;
	yDir = 0;
}

void Robot::handleEvent(SDL_Event& e, int JOYSTICK_DEAD_ZONE)
{
	//If a key was pressed
	if (e.type == SDL_JOYAXISMOTION)
	{


		if (e.jaxis.which == 0)
		{

			//X axis motion
			if (e.jaxis.axis == 0)
			{

				//Left of dead zone
				if (e.jaxis.value < -JOYSTICK_DEAD_ZONE)
				{
					mVelX -= DOT_VEL;
					xDir = -1;
				}
				//Right of dead zone
				else if (e.jaxis.value > JOYSTICK_DEAD_ZONE)
				{
					mVelX += DOT_VEL;
					xDir = 1;
				}
				else
				{
					xDir = 0;
					mVelX = 0;

				}
			}
			//Y axis motion
			else if (e.jaxis.axis == 1)
			{

				//Below of dead zone
				if (e.jaxis.value < -JOYSTICK_DEAD_ZONE)
				{
					mVelY -= DOT_VEL;

					yDir = -1;
				}
				//Above of dead zone
				else if (e.jaxis.value > JOYSTICK_DEAD_ZONE)
				{
					mVelY += DOT_VEL;
					yDir = 1;

				}
				else //dead zone
				{
					yDir = 0;
					mVelY = 0;

				}
			}
		}

	}





}

void Robot::move(int SCREEN_WIDTH, int SCREEN_HEIGHT)
{

	//Move the dot left or right
	mPosX += mVelX;

	//If the dot went too far to the left or right
	if ((mPosX < 0) || (mPosX > SCREEN_WIDTH))
	{
		//Move back
		mPosX -= mVelX;
	}

	//Move the dot up or down
	mPosY += mVelY;
	//If the dot went too far up or down
	if ((mPosY < 0) || (mPosY > SCREEN_HEIGHT))
	{
		//Move back
		mPosY -= mVelY;
	}
}

void Robot::render(SDL_Renderer* gRenderer, LTexture gRobotTexture)
{
	//Show the arrow
	gRobotTexture.render(mPosX, mPosY, NULL, gRenderer);
}

int Robot::getxDir()
{
	return xDir;
}

int Robot::getyDir()
{
	return yDir;
}

int Robot::getPosX()
{
	return mPosX;
}

int Robot::getPosY()
{
	return mPosY;
}