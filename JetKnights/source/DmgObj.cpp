#pragma once
#include "DmgObj.h"

DmgObj::DmgObj() {
	//Initialize the Position
	counter = 0;
	startPosX = 1;
	startPosY = 300;
	mPosX = 300;
	mPosY = 300;
	mAngle = -45;
	mCollider.w = 10;
	mCollider.h = 10;
	mCollider.x = 300;
	mCollider.y = 300;
	//Set damage amount
	damage = 5;
	//Set Object Speed
	mSpeed = 1;
}

//DmgObj::DmgObj(int posX, int posY, float angle, int projectileKey) {
//	//Initialize the Position
//	counter = 0;
//	startPosX = posX;
//	startPosY = posX;
//	mPosX = 0;
//	mPosY = 0;
//	mAngle = angle;
//
//	if (projectileKey == 1) {
//		//Set collision box dimension
//		mCollider.w = 5;
//		mCollider.h = 5;
//		mCollider.x = mPosX;
//		mCollider.y = mPosY;
//		//Set damage amount
//		damage = 5;
//		//Set Object Speed
//		mSpeed = 5;
//	}
//	else {
//		printf("Failed to Create DmgObj: Unknown bullet type.");
//		//Obj.destroy?
//	}
//}


void DmgObj::move(int SCREEN_WIDTH, int SCREEN_HEIGHT, SDL_Rect b) {
	mPosX = startPosX + counter * mSpeed * cos(mAngle);
	mPosY = startPosY + counter * mSpeed * sin(mAngle);
	mCollider.x = mPosX;
	mCollider.y = mPosY;

	if ((mPosX < 0) || (mPosX > SCREEN_WIDTH) || (mPosY < 0) || (mPosY > SCREEN_HEIGHT) || checkCollision(mCollider, b)) {
		//Move back
		counter -= 1;
		mPosX = startPosX + counter * mSpeed * cos(mAngle);
		mPosY = startPosY + counter * mSpeed * sin(mAngle);
	}
	counter += 1;
}

void DmgObj::render(SDL_Renderer* gRenderer, LTexture gRobotTexture)
{
	//Show the arrow
	gRobotTexture.render(mPosX, mPosY, NULL, gRenderer);
}

bool DmgObj::checkCollision(SDL_Rect a, SDL_Rect b) {
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

int DmgObj::getPosX() {
	return mPosX;
}

int DmgObj::getPosY() {
	return mPosY;
}

const SDL_Rect* DmgObj::getHitbox() {
	return &mCollider;
}