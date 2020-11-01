#include "NewRobot.h"



NewRobot::NewRobot() : GameObject() {
	joyX = 0;
	joyY = 0;
	mSpeed = 0;
	radius = 0;
	hitboxOffsetX = 0;
	hitboxOffsetY = 0;
	boost = 0;
	health = 100;
	player = 0;

}

NewRobot::NewRobot(int x, int y, float angle, SDL_Renderer* renderer) : GameObject(x, y, angle, renderer) {
	// 'joyX' and 'joyY' hold the all the value of the joystick +-320000
	joyX = 0;
	joyY = 0;

	mSpeed = 0;
	radius = 40;

	boost = 0;
	health = 100;
	player = 0;
}

NewRobot::NewRobot(int x, int y, float angle, SDL_Renderer* renderer, LTexture* ltexture) : GameObject(x, y, angle, renderer, ltexture) {
	// 'joyX' and 'joyY' hold the all the value of the joystick +-320000
	joyX = 0;
	joyY = 0;

	mSpeed = 0;
	radius = 40;
	boost = 0;

	health = 100;
	player = 0;
}

void NewRobot::handleEvent(SDL_Event e) {

	//Controller input
	if (e.type == SDL_CONTROLLERAXISMOTION) {
		//If player 1 input
		if (e.caxis.which == player) {
			//X axis motion
				if (e.caxis.axis == SDL_CONTROLLER_AXIS_LEFTX) {
					joyX = e.caxis.value;
					// Set speed depending on dead zone
					if (!inDeadCircle()) {
						mSpeed = MAX_SPEED + boost;
					}
					else {
						mSpeed = 0;
					}
				}
				//Y axis motion
				else if (e.caxis.axis == SDL_CONTROLLER_AXIS_LEFTY) {
					joyY = e.caxis.value;
					// Set speed depending on dead zone
					if (!inDeadCircle()) {
						mSpeed = MAX_SPEED + boost;
					}
					else {
						mSpeed = 0;
					}
				}
				//Trigger press
				else if (e.caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERLEFT) {
					if (e.caxis.value > TRIGGER_DEAD_ZONE) {
						boost = 600;
					}
					else {
						boost = 0;
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

void NewRobot::update(float timeStep) {
	//std::cout << timeStep << std::endl;
	if (health <= 0) {
		isDead = true;
	}
	else {
		if (relX != NULL && relY != NULL) {
			posX += *relX + getVelX() * timeStep;
			posY += *relY + getVelY() * timeStep;
		}
		else {
			posX += getVelX() * timeStep;
			posY += getVelY() * timeStep;
		}
		if (hitbox != NULL) {
			hitbox->setPos(posX, posY);
			//std::cout << "POS X:" << hitbox->getPosX() << std::endl;
			//std::cout << "POS Y:" << hitbox->getPosY() << std::endl;

		}
	}
}

//void NewRobot::updateCollision(int screenWidth, int screenHeight, Hitbox* b) {
//	if (hitbox != NULL) {
//		if (hitbox->chkBorderCollisionX(screenWidth) || hitbox->chkCollision(b)) {
//			posX -= getVelX();
//			hitbox->setPosX(posX);
//		}
//		if (hitbox->chkBorderCollisionY(screenHeight) || hitbox->chkCollision(b)) {
//			posY -= getVelY();
//			hitbox->setPosY(posY);
//		}
//	}
//	else {
//		//Check if bullet hits screen boundaries
//		if (hitbox->chkBorderCollisionX(screenWidth)) {
//			posX -= getVelX();
//		}
//		if (hitbox->chkBorderCollisionY(screenHeight)) {
//			posY -= getVelY();
//		}
//	}
//}

void NewRobot::setPlayer(int p) {
	player = p;
}

bool NewRobot::updateBorderCollision(int screenWidth, int screenHeight, float stepTimer) {
	if (hitbox->chkBorderCollisionX(screenWidth)) {
		posX -= getVelX() * stepTimer;
		hitbox->setPosX(posX);
		return true;
	}
	else if (hitbox->chkBorderCollisionY(screenHeight)) {
		posY -= getVelY() * stepTimer;
		hitbox->setPosY(posY);
		return true;
	}
	return false;
}

void NewRobot::updateCollision(GameObject* b, float timeStep) {
	if (chkCollision(b)) {
			posX -= getVelX() * timeStep;
			posY -= getVelY() * timeStep;
	}
}

//bool NewRobot::isPlayerBoosting(SDL_Event e) {
//
//	static int num = 0;
//
//	if (e.type == SDL_CONTROLLERAXISMOTION) {
//		//Controller input
//
//		//If player 1 input
//		if (e.caxis.which == 0) {
//
//			if (e.caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERLEFT) {
//				//std::cout << "WHAT!!!" << std::endl;
//				//std::cout << e.caxis.value << std::endl;
//				if (e.caxis.value > RIGHT_TRIGGER_DEAD_ZONE) {
//					num = e.caxis.value;
//					return true;
//				}
//				else {
//					num = e.caxis.value;
//
//					return false;
//				}
//			}
//		}
//	}
//	else if (num > RIGHT_TRIGGER_DEAD_ZONE) {
//		return true;
//	}
//	else {
//		return false;
//	}
//}

void NewRobot::boostOn() {
	std::cout << "BOOSTING" << std::endl;
	boost = 600;
}
void NewRobot::boostOff() {
	boost = 0;
}

void NewRobot::updateCollision(NewRobot* b, float timeStep) {
	if (chkCollision(b)) {
		posX -= getVelX() * timeStep;
		posY -= getVelY() * timeStep;
	}
}

void NewRobot::updateCollision(Bullet* b, float timeStep) {
	if (chkCollision(b)) {
		health -= b->getDamage();
	}
}

int NewRobot::getHealth() {
	return health;
}