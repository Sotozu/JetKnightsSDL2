#pragma once
#include <iostream>
#include <cmath>
#include <SDL_gamecontroller.h>
#include <typeinfo>

#include "GameObject.h"
#include "Bullet.h"
#include "Robot_Sounds.h"



class NewRobot : public GameObject{
public:
	//Constructors
	NewRobot();
	NewRobot(int x, int y, float angle, SDL_Renderer* renderer);
	NewRobot(int x, int y, float angle, SDL_Renderer* renderer, RelTexture* ltexture);

	//Mutators
	void handleEvent(SDL_Event e);
	//void update(float);

	void updatePosX(float);

	void updatePosY(float);

	void pauseRobotSounds();
	void unpauseRobotSounds();

	void pauseRobot();
	void unpauseRobot();
	void boostOn();
	void boostOff();
	void setPlayer(int);

	void updateBorderCollision(int, int, float);
	void updateCollision(GameObject*, float);
	void updateCollision(NewRobot*, float);
	void updateCollision(Bullet*, float);

	void updateCollisionX(GameObject*, float);
	void updateCollisionX(NewRobot*, float);

	void updateCollisionY(GameObject*, float);
	void updateCollisionY(NewRobot*, float);


	//Accessors
	int getJoyX();
	int getJoyY();

	int getVelX();
	int getVelY();
	float getJoyAngle();
	int getHealth();

	//Data
	int health;
	//int energy;

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

	int player;
	const int JOYSTICK_DEAD_ZONE = 8000;
	const int TRIGGER_DEAD_ZONE = 5000;

	bool inDeadCircle();
	bool isPaused;

	Robot_Sounds robotSound;
};

