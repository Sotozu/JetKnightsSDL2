#include "NewRobot.h"



NewRobot::NewRobot() : GameObject() {
	joyX = 0;
	joyY = 0;
	mSpeed = 0;
	radius = 0;
	hitboxOffsetX = 0;
	hitboxOffsetY = 0;
}

NewRobot::NewRobot(int x, int y, float angle, SDL_Renderer* renderer) : GameObject(x, y, angle, renderer) {
	// 'joyX' and 'joyY' hold the all the value of the joystick +-320000
	joyX = 0;
	joyY = 0;

	mSpeed = 0;
	radius = 40;

}

NewRobot::NewRobot(int x, int y, float angle, SDL_Renderer* renderer, LTexture* ltexture) : GameObject(x, y, angle, renderer, ltexture) {
	// 'joyX' and 'joyY' hold the all the value of the joystick +-320000
	joyX = 0;
	joyY = 0;

	mSpeed = 0;
	radius = 40;
}

void NewRobot::handleEvent(SDL_Event e) {
	//Controller input
	if (e.type == SDL_CONTROLLERAXISMOTION) {
		//If player 1 input
		if (e.caxis.which == 0) {
			//X axis motion
			if (e.caxis.axis == 0) {							
				joyX = e.caxis.value;
				// Set speed depending on dead zone
				if (!inDeadCircle()) {
					mSpeed = MAX_SPEED;
				}
				else {
					mSpeed = 0;
				}
			}
			//Y axis motion
			else if (e.caxis.axis == 1) {						
				joyY = e.caxis.value;
				// Set speed depending on dead zone
				if (!inDeadCircle()) {			
					mSpeed = MAX_SPEED;
				}
				else {
					mSpeed = 0;
				}
			}
		}
	}
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


float NewRobot::getJoyAngle() {
	return atan2((double)joyY, (double)joyX) * (180.0 / M_PI);
}

int NewRobot::getJoyX() {
	return joyX;
}

int NewRobot::getJoyY() {
	return joyY;
}

int NewRobot::getVelX() {
	return mSpeed *cos(getJoyAngle() * (M_PI / 180));
}
int NewRobot::getVelY() {
	return mSpeed * sin(getJoyAngle() * (M_PI / 180));
}

void NewRobot::update() {
	posX += getVelX();
	posY += getVelY();
	if (hitbox != NULL){
		hitbox->setPos(posX, posY);
	}
}

bool NewRobot::chkCollision(int screenW, int screenH, Hitbox* b) {
	if (hitbox != NULL) {
		//Check if bullet hits screen boundaries
		if ((hitbox->x < 0) || (hitbox->x + hitbox->w > screenW) || (hitbox->y < 0) || (hitbox->y + hitbox->h > screenH)) {
			return true;
		}
		else if (b != NULL) {
			return hitbox->chkCollision(b);
		}
	}
	return false;
}