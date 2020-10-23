#pragma once
#include <iostream>
#include <cmath>
#include <SDL_gamecontroller.h>
#include <typeinfo>
#include "GameObject.h"
#include "Bullet.h"



class NewRobot : public GameObject{
public:
	//Constructors
	NewRobot();
	NewRobot(int x, int y, float angle, SDL_Renderer* renderer);
	NewRobot(int x, int y, float angle, SDL_Renderer* renderer, LTexture* ltexture);

	//Mutator
	void handleEvent(SDL_Event e);
	bool isPlayerBoosting(SDL_Event e);
	void update(float);
	void boostOn();
	void boostOff();
	void setPlayer(int);


	//Accessor
	int getJoyX();
	int getJoyY();

	int getVelX();
	int getVelY();
	float getJoyAngle();
	int getHealth();

	bool updateBorderCollision(int, int, float);
	void updateCollision(GameObject*, float);
	void updateCollision(NewRobot*, float);
	void updateCollision(Bullet*, float);
	

	//template <class T>
	//void updateCollision2(int screenWidth, int screenHeight, T* b) {

	//	if (hitbox->chkBorderCollisionX(screenWidth)) {
	//		posX -= getVelX();
	//		hitbox->setPosX(posX);
	//	}
	//	else if (hitbox->chkBorderCollisionY(screenHeight)) {
	//		posY -= getVelY();
	//		hitbox->setPosY(posY);
	//	}
	//	else if (chkCollision(b)) {
	//		// Determine the type of class and decide form of update
	//		std::string s = typeid(b).name();
	//		std::cout << s << std::endl;
	//		if (s == "class GameObject * __ptr64" || s == "class NewRobot * __ptr64") {
	//			posX -= getVelX();
	//			posY -= getVelY();
	//		}
	//		else if (s == "class Bullet * __ptr64") {
	//			health -= b->getDamage();
	//			//std::cout << "obj was bullet?" << std::endl;
	//		}
	//	}
	//}


private:
	// the robot speed is based on fps/1000; 
	const int MAX_SPEED = 600;
	static const int ROB_VEL = 1;
	static const int ROB_MAX_VEL = 1200;
	static const int ROB_BOOST_SPEED = 600;
	int joyX;
	int joyY;

	int radius;
	int mSpeed;
	int boost;

	int health;
	int player;
	const int JOYSTICK_DEAD_ZONE = 8000;
	const int TRIGGER_DEAD_ZONE = 5000;

	bool inDeadCircle();
};

