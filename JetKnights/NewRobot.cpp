#include "NewRobot.h"



NewRobot::NewRobot() : GameObject() {
	joyX = 0;
	joyY = 0;
	mSpeed = 0;
	radius = 0;
	hitboxOffsetX = 0;
	hitboxOffsetY = 0;
	health = 100;
	player = 0;
}

NewRobot::NewRobot(int x, int y, float angle, SDL_Renderer* renderer) : GameObject(x, y, angle, renderer) {
	// 'joyX' and 'joyY' hold the all the value of the joystick +-320000
	joyX = 0;
	joyY = 0;

	mSpeed = 0;
	radius = 40;
	health = 100;
	player = 0;
}

NewRobot::NewRobot(int x, int y, float angle, SDL_Renderer* renderer, LTexture* ltexture) : GameObject(x, y, angle, renderer, ltexture) {
	// 'joyX' and 'joyY' hold the all the value of the joystick +-320000
	joyX = 0;
	joyY = 0;

	mSpeed = 0;
	radius = 40;
	health = 100;
	player = 0;
}

void NewRobot::handleEvent(SDL_Event e) {

	//Controller input
	if (e.type == SDL_CONTROLLERAXISMOTION) {
		//If player 1 input
		if (e.caxis.which == player) {
			//X axis motion
			
				std::cout << "BITCHES" << std::endl;
				if (e.caxis.axis == SDL_CONTROLLER_AXIS_LEFTX) {
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
				else if (e.caxis.axis == SDL_CONTROLLER_AXIS_LEFTY) {
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
	//std::cout << health << std::endl;
	if (health <= 0) {
		isDead = true;
	}
	else {
		posX += getVelX();
		posY += getVelY();
		if (hitbox != NULL) {
			hitbox->setPos(posX, posY);
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

bool NewRobot::updateBorderCollision(int screenWidth, int screenHeight) {
	if (hitbox->chkBorderCollisionX(screenWidth)) {
		posX -= getVelX();
		hitbox->setPosX(posX);
		return true;
	}
	else if (hitbox->chkBorderCollisionY(screenHeight)) {
		posY -= getVelY();
		hitbox->setPosY(posY);
		return true;
	}
	return false;
}

void NewRobot::updateCollision(GameObject* b) {
	if (chkCollision(b)) {
			posX -= getVelX();
			posY -= getVelY();
	}
}

void NewRobot::updateCollision(NewRobot* b) {
	if (chkCollision(b)) {
		posX -= getVelX();
		posY -= getVelY();
	}
}

void NewRobot::updateCollision(Bullet* b) {
	//std::cout << "checking bullet collision" << std::endl;
	if (chkCollision(b)) {
		//std::cout << "bullet has collided" << std::endl;
		health -= b->getDamage();
		//b->isDead = true;
	}
}

int NewRobot::getHealth() {
	return health;
}