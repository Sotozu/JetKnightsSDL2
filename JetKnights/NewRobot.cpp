#include "NewRobot.h"



NewRobot::NewRobot() : GameObject() {
	gRenderer = NULL;
	texture = NULL;

	robotVelX = 0;
	robotVelY = 0;


	dirX = 0;
	dirY = 0;

	joyX = 0;
	joyY = 0;

	radius = 0;

	ang = 0;

	hitboxOffsetX = 0;
	hitboxOffsetY = 0;
}

NewRobot::NewRobot(int x, int y, float angle, SDL_Renderer* renderer) : GameObject(x, y, angle, renderer) {
	/*
	'joyX' and 'joyY' hold the all the value of the joystick +-320000
	*/
	joyX = 0;
	joyY = 0;
	/*
	Hold the x and y values of the joystick only outside of the deadzone.
	*/
	dirX = 0;
	dirY = 0;

	robotVelX = 0;
	robotVelY = 0;

	radius = 40;

}

NewRobot::NewRobot(int x, int y, float angle, SDL_Renderer* renderer, LTexture* ltexture) : GameObject(x, y, angle, renderer, ltexture) {
	/*
'joyX' and 'joyY' hold the all the value of the joystick +-320000
*/
	joyX = 0;
	joyY = 0;
	/*
	Hold the x and y values of the joystick only outside of the deadzone.
	*/
	dirX = 0;
	dirY = 0;

	robotVelX = 0;
	robotVelY = 0;

	radius = 40;
}


/*
What variables from base object GameObject be used here? How can we
*/
void NewRobot::handleEvent(SDL_Event e) {
	//If a key was pressed
	if (e.type == SDL_CONTROLLERAXISMOTION)
	{
			if (e.caxis.which == 0) //Which controller ID
			{

				//X axis motion
				if (e.caxis.axis == 0)
				{

					//Left of dead zone
					if (e.caxis.value < -JOYSTICK_DEAD_ZONE)
					{
						robotVelX--;

						//player update. Cant go faster than max velocity
						if (abs(robotVelX - ROB_VEL) < ROB_MAX_VEL) {
							robotVelX -= ROB_VEL;
						}

					}
					//Right of dead zone
					else if (e.caxis.value > JOYSTICK_DEAD_ZONE)
					{

						//player update. Cant go faster than max velocity
						if ((robotVelX + ROB_VEL) < ROB_MAX_VEL) {
							robotVelX += ROB_VEL;
						}

					}
					else
					{

						robotVelX = 0;


					}
				}
				//Y axis motion
				else if (e.caxis.axis == 1)
				{

					//Below of dead zone
					if (e.caxis.value < -JOYSTICK_DEAD_ZONE)
					{
						if (abs(robotVelY - ROB_VEL) < ROB_MAX_VEL) {
							robotVelY -= ROB_VEL;
						}

					}
					//Above of dead zone
					else if (e.caxis.value > JOYSTICK_DEAD_ZONE)
					{
						if ((robotVelX + ROB_VEL) < ROB_MAX_VEL) {
							robotVelY += ROB_VEL;
						}
					}
					else //dead zone
					{

						robotVelY = 0;

					}
				}
			}

	}
}





void NewRobot::getAngle() {
	//Calculate angle
	double joyAngle = atan2((double)dirY, (double)dirX) * (180.0 / M_PI);
	ang = joyAngle;
	//return joyAngle;
}

int NewRobot::getJoyX() {
	return joyX;
}

int NewRobot::getJoyY() {
	return joyY;
}


void NewRobot::update() {
	//getAngle();
	//std::cout << "VELOCITY Y:" <<robotVelY << std::endl;
	//std::cout << "VELOCITY X:" << robotVelX << std::endl;

	posX += robotVelX;
	posY += robotVelY;

	hitbox.setPos(posX, posY);

}

bool NewRobot::inDeadCircle() {
	//Calculates a dead zone circle as opposed to dead zone cross
	if (JOYSTICK_DEAD_ZONE > sqrt(pow(joyX, 2) + pow(joyY, 2))) {
		return true;
	}
	else {
		return false;
	}
}