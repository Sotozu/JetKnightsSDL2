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

NewRobot::NewRobot(int x, int y, float angle, SDL_Renderer* renderer, RelTexture* ltexture) : GameObject(x, y, angle, renderer, ltexture) {
	// 'joyX' and 'joyY' hold the all the value of the joystick +-320000
	joyX = 0;
	joyY = 0;

	mSpeed = 0;
	radius = 40;
	boost = 0;

	health = 100;
	player = 0;
}

// Handles controller events that the robot should respond to
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
						if (boost != 600) {
							robotSound.turnThrusterOn();
						}
						boost = 600;
					}
					else {
						if (boost == 600) {
							robotSound.turnThrusterOff();
						}
						boost = 0;
					}

				}
		}
	}


}

//Calculates a dead zone circle as opposed to dead zone cross
bool NewRobot::inDeadCircle() {
	if (JOYSTICK_DEAD_ZONE > sqrt(pow(joyX, 2) + pow(joyY, 2))) {
		return true;
	}
	else {
		return false;
	}
}

// Gets angle of the Joystick
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

// Robot update function
void NewRobot::update(float timeStep) {
	//std::cout << timeStep << std::endl;
	if (!isDead) {
		relX += getVelX() * timeStep;
		relY += getVelY() * timeStep;
		updatePos();
		for(auto &hitbox : hitboxes) {
			hitbox.setPos(posX, posY);
		}
		updateChildren(timeStep);
	}
}

void NewRobot::setPlayer(int p) {
	player = p;
}

void NewRobot::updateBorderCollision(int screenWidth, int screenHeight, float stepTimer) {
	for (auto hitbox : hitboxes) {
		if (hitbox.chkBorderCollisionX(screenWidth)) {
			relX -= getVelX() * stepTimer;
			updatePos();
		}
		if (hitbox.chkBorderCollisionY(screenHeight)) {
			relY -= getVelY() * stepTimer;
			updatePos();
		}
	}
}

void NewRobot::updateCollision(GameObject* b, float timeStep) {
	if (chkCollision(b)) {
			relX -= getVelX() * timeStep;
			relY -= getVelY() * timeStep;
			updatePos();
	}
}

void NewRobot::boostOn() {
	std::cout << "BOOSTING" << std::endl;
	boost = 600;
}
void NewRobot::boostOff() {
	boost = 0;
}

// When the robot collides with another robot
void NewRobot::updateCollision(NewRobot* b, float timeStep) {
	if (chkCollision(b)) {
		relX -= getVelX() * timeStep;
		relY -= getVelY() * timeStep;
		updatePos();
	}
}

// When the robot collides with a bullet
void NewRobot::updateCollision(Bullet* b, float timeStep) {
	if (chkCollision(b)) {
		health -= b->getDamage();
		if (health <= 0) {
			isDead = true;
		}
	}
}

int NewRobot::getHealth() {
	return health;
}