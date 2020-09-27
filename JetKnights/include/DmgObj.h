#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include "LTexture.h"


class DmgObj
{
public:
	//The dimensions of the robot
	static const int HITBOX_WIDTH = 32;
	static const int HITBOX_HEIGHT = 32;

	//Initializes the variables
	DmgObj();
	//DmgObj(int posX, int posY, float angle, int projectileKey);

	//Moves the dot
	void move(int SCREEN_WIDTH, int SCREEN_HEIGHT, SDL_Rect b);

	//Shows the Object on the screen
	void render(SDL_Renderer* gRenderer, LTexture gRobotTexture);

	int   getPosX();
	int   getPosY();

	const SDL_Rect* getHitbox();

	bool checkCollision(SDL_Rect a, SDL_Rect b);

private:
	//The X and Y offsets of the dot
	int startPosX, startPosY;
	int mPosX, mPosY;

	float mAngle;
	float mSpeed;
	int damage;
	int counter;

	//Dot's collision box
	SDL_Rect mCollider;
};