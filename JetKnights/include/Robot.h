#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Robot.h"
#include "LTexture.h"
//#include "Weapon.h"

//forward declaration
class Weapon;

class Robot
{
public:
	//The dimensions of the robot
	static const int DOT_WIDTH = 20;
	static const int DOT_HEIGHT = 20;

	//Maximum axis velocity of the robot
	static const int DOT_VEL = 3;

	//Initializes the variables

	Robot(Weapon*);

	//Takes key presses and adjusts the robot's velocity
	void handleEvent(SDL_Event& e, int JOYSTICK_DEAD_ZONE);

	//Moves the dot
	void move(int SCREEN_WIDTH, int SCREEN_HEIGHT);

	//Shows the robot on the screen
	void render(SDL_Renderer* gRenderer, LTexture gRobotTexture, LTexture gWeapon1);


	int getxDir();
	int getyDir();

	int getPosX();
	int getPosY();

	int getWeaponPosX();
	int getWeaponPosY();


private:
	//The X and Y offsets of the dot

	Weapon* s1;

	int mPlayerPosX, mPlayerPosY;

	//The velocity of the dot
	int mPlayerVelX, mPlayerVelY;

	//Normalized directions
	int xPlayerDir;
	int yPlayerDir;
};