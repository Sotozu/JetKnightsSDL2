#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Robot.h"
#include "LTexture.h"
#include "Weapon.h"

//forward declaration
class Weapon;
class LTexture;

class Robot
{
public:
	//The dimensions of the robot
	static const int DOT_WIDTH = 20;
	static const int DOT_HEIGHT = 20;

	//Maximum axis velocity of the robot
	static const int DOT_VEL = 1;

	//Constructor
	Robot(Weapon*, LTexture*);

	//Accessors
	int getxDir();
	int getyDir();

	int getPosX();
	int getPosY();

	int getWeaponPosX();
	int getWeaponPosY();

	//Processes
	void handleEvent(SDL_Event& e, int JOYSTICK_DEAD_ZONE);	//Takes key presses and adjusts the robot's velocity
	void update(int SCREEN_WIDTH, int SCREEN_HEIGHT); //Moves the dot
	void render(SDL_Renderer* gRenderer); //Shows the robot on the screen
	

	


private:
	//The X and Y offsets of the dot

	Weapon* s1;
	LTexture* robotTexture;

	int mPlayerPosX, mPlayerPosY;

	void determineCenterPositions();

	//The velocity of the dot
	int mPlayerVelX, mPlayerVelY;

	//Normalized directions
	int xPlayerDir;
	int yPlayerDir;

	int playerCenterAdjustmentX, playerCenterAdjustmentY;
};