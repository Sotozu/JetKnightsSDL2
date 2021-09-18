#include "NewRobot.h"



NewRobot::NewRobot() {
	joyX = 0;
	joyY = 0;

	mSpeed = 0;
	radius = 0;

	boost = 0;
	health = 100;
	player = 0;
	triggerAxisValue = 0;

	isPaused = false;
	hasJustBeenPaused = false;
	isThrusterCurrentlyOn = false;
	thrusterSwitchOn = false;
	wasThrusterAlreadyOn = false;
	thrusterOnBeforePause = false;

	gameController = NULL;
}

NewRobot::NewRobot(int m_x, int m_y, float angle, SDL_GameController* CONTROLLER) {
	// 'joyX' and 'joyY' hold the all the value of the joystick +-320000
	joyX = 0;
	joyY = 0;

	mSpeed = 0;
	radius = 40;

	boost = 0;
	health = 100;
	player = 0;
	triggerAxisValue = 0;

	isPaused = false;
	hasJustBeenPaused = false;
	isThrusterCurrentlyOn = false;
	thrusterSwitchOn = false;
	wasThrusterAlreadyOn = false;
	thrusterOnBeforePause = false;

	gameController = CONTROLLER;

	m_x = m_x;
	m_y = m_y;
	m_ang = angle;
}

jks::Type NewRobot::getType() {
	return jks::Type::ROBOT;
}

void NewRobot::pauseRobotSounds() {
	robotSound.pauseThruster();
}

void NewRobot::unpauseRobotSounds() {
	robotSound.resumeThruster();
}

void NewRobot::robotPaused(SDL_Event e) {
	isPaused = true;

	robotSound.pauseThruster();

	if (e.type == SDL_CONTROLLERAXISMOTION) {
			//If player 1 input
		if (e.caxis.which == player) {
			onEventJoyX(e);
			//Y axis motion
			onEventJoyY(e);
			if (e.caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERLEFT) {

				//TRIGGER HELD DOWN
				if (e.caxis.value > TRIGGER_DEAD_ZONE) {
					if (isThrusterCurrentlyOn == false) {

						/*
						1. is paused
						2. thrusters were set to OFF before
						3. currently holding down the trigger
						4. Thruster should be ON when we unpause and a NEW THRUSTER ON SOUND SHOULD BE PLAYED!
						thrusterSwitchOn = true;


					}
					else if (isThrusterCurrentlyOn == true) {
						/*
						1. is paused
						2. thruster were set to ON before
						3. currently holding down the trigger
						4. Thruster should be set to ON when unpause and RESUME THRUSTER SOUND
						*/
						thrusterSwitchOn = true;


					}

				}
				//TRIGGER NOT HELD DOWN
				else if (e.caxis.value <= TRIGGER_DEAD_ZONE) {

					if (isThrusterCurrentlyOn == false) {
						/*
						1. is paused
						2. thruster were set to OFF before
						3. NOT holding down the trigger
						4. Thruster should be set to OFF when unpause and A COMPLETE RESET TO THE THRUSTER SOUND SYSTEM
						*/
						thrusterSwitchOn = false;

					}
					else if (isThrusterCurrentlyOn == true) {
						/*
						1. is paused
						2. thruster were set to ON before
						3. not holding down the trigger
						4. Thruster should be OFF when unpause and A NEW THRUSTER OFF SOUND SHOULD BE PLAYED!
						*/
						thrusterSwitchOn = false;


					}
				}
			}

		}
	}
		

}
void NewRobot::robotUnpause() {
	//WE HAVE NOW UNPAUSED THE GAME

	if (isThrusterCurrentlyOn == false && thrusterSwitchOn == true) {
		//NEW THRUSTER SOUND
		robotSound.turnThrusterOn();	
		boost = 600;
	}
	else if (isThrusterCurrentlyOn == false && thrusterSwitchOn == false){
		//RESUME THRUSTER SOUND
		robotSound.resumeThruster();
		boost = 600;


	}
	else if (isThrusterCurrentlyOn == false && thrusterSwitchOn == true) {
		//NO SOUND

	}
	else if (isThrusterCurrentlyOn == true && thrusterSwitchOn == false) {
		//TURN THRUSTER OFF SOUND
		boost = 0;
		robotSound.turnThrusterOff();

	}

}

void NewRobot::onEventJoyX(SDL_Event e) {
	if (e.type == SDL_CONTROLLERAXISMOTION) {
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
	}
}

void NewRobot::onEventJoyY(SDL_Event e) {
	if (e.type == SDL_CONTROLLERAXISMOTION) {
		if (e.caxis.axis == SDL_CONTROLLER_AXIS_LEFTY) {
			joyY = e.caxis.value;
			// Set speed depending on dead zone
			if (!inDeadCircle()) {
				mSpeed = MAX_SPEED + boost;
			}
			else {
				mSpeed = 0;
			}
		}
	}
}

void NewRobot::onEventLeftTrigger(SDL_Event e) {
	if (e.type == SDL_CONTROLLERAXISMOTION) {
		if (e.caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERLEFT) {
			triggerAxisValue = e.caxis.value;

			if (triggerAxisValue > TRIGGER_DEAD_ZONE) {
				//If the trigger is pressed to turn thruster on 
				//AND the thruster has not been turned on yet THEN play the thruster ON sound
				if (thrusterSwitchOn == false) {

					thrusterSwitchOn = true;
					robotSound.turnThrusterOn();
					boost = 600;
				}
				isThrusterCurrentlyOn = true;

			}
			else if (triggerAxisValue <= TRIGGER_DEAD_ZONE) {

				if (thrusterSwitchOn == true) {
					robotSound.turnThrusterOff();
					thrusterSwitchOn = false;
					boost = 0;
				}
				isThrusterCurrentlyOn = false;

			}
		}
	}
}

void NewRobot::onEventButtonB(SDL_Event e) {
	if (e.type == SDL_CONTROLLERBUTTONDOWN) {
		if (e.cbutton.button == SDL_CONTROLLER_BUTTON_B) {
			//nextWeapon();
		}
	}
}

// Handles controller events that the robot should respond to
void NewRobot::onEvent(SDL_Event e) {
	//If player 1 input
	if (e.caxis.which == player) {
		onEventJoyX(e);        // X axis motion
		onEventJoyY(e);        // Y axis motion
		onEventLeftTrigger(e); // Fire weapon trigger
		onEventButtonB(e);     // Switch weapon button
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

void NewRobot::onUpdate(float timestep) {
	updatePosX(timestep);
	updatePosY(timestep);
	
	updateCollision(timestep);

	render();
}

void NewRobot::updateCollision(float timestep) {
	std::list<IGameObject*> allObjs = getAllObjects();

	for (auto otherObj : allObjs) {
		if (isColliding(otherObj)) {
			onCollision(otherObj, timestep);
		}
	}
}

void NewRobot::renderHitbox() {
	jks::Position posAbs = getPositionAbsolute();

	for (Hitbox& hitbox : hitboxes) {
		hitbox.renderAll(posAbs.m_x, posAbs.m_y);
	}
}

void NewRobot::updatePosX(float timeStep) {
	if (!isDead) {
		m_x += getVelX() * timeStep;
	}
}

void NewRobot::updatePosY(float timeStep) {
	if (!isDead) {
		m_y += getVelY() * timeStep;
	}
}

void NewRobot::setPlayer(int p) {
	player = p;
}

void NewRobot::updateBorderCollision(int screenWidth, int screenHeight, float stepTimer) {
	for (auto hitbox : hitboxes) {
		if (hitbox.chkBorderCollisionX(screenWidth)) {
			m_x -= getVelX() * stepTimer;
		}
		if (hitbox.chkBorderCollisionY(screenHeight)) {
			m_y -= getVelY() * stepTimer;
		}
	}
}

int NewRobot::getHealth() {
	return health;
}

void NewRobot::boostOn() {
	boost = 600;
}
void NewRobot::boostOff() {
	boost = 0;
}

void NewRobot::addDefaultHitbox() {
	Hitbox hitbox = Hitbox(50, 50);
	addHitbox(hitbox);
}


void NewRobot::onCollision(IGameObject* otherObj, float timestep) {
	// Perform behavior based on object type
	switch (otherObj->getType()) {
	case jks::Type::OBSTACLE:
		m_x -= getVelX() * timestep;
		m_y -= getVelY() * timestep;
		break;
	case jks::Type::ROBOT:
		m_x -= getVelX() * timestep;
		m_y -= getVelY() * timestep;
		break;
	case jks::Type::BULLET:
		//health -= otherObj.getDamage();
		if (health <= 0) {
			isDead = true;
		}
		break;
	default:
		// Do nothing
		break;
	}
}



/*






// X

void NewRobot::updateCollisionX(GameObject* b, float timeStep) {
	if (chkCollision(b)) {
		relX -= getVelX() * timeStep;
		updatePos();
	}
}



// When the robot collides with another robot
void NewRobot::updateCollisionX(NewRobot* b, float timeStep) {
	if (chkCollision(b)) {
		relX -= getVelX() * timeStep;
		updatePos();
	}
}


// Y

void NewRobot::updateCollisionY(GameObject* b, float timeStep) {
	if (chkCollision(b)) {
		relY -= getVelY() * timeStep;
		updatePos();
	}
}

// When the robot collides with another robot
void NewRobot::updateCollisionY(NewRobot* b, float timeStep) {
	if (chkCollision(b)) {
		relY -= getVelY() * timeStep;
		updatePos();
	}
}

// Will deactivate the current weapon and activate the next one
void NewRobot::nextWeapon() {
	// Get "list" of weapons
	// Currently only searches direct children
	std::vector<NewWeapon*> weapons;
	for (auto& varObj : children) {
		if (NewWeapon* weapon = std::get_if<NewWeapon>(&varObj)) {
			weapons.push_back(weapon);
		}
	}
	// Activate and deactivate based on index
	if (weapons.size() <= 1) {  // dont think i need this check, but will keep for now
		return;
	}
	else {
		for (int i = 0 ; i < weapons.size() ; i++ ) {
			if (weapons[i]->isActive) {
				weapons[i]->isActive = false;
				weapons[(i + 1) % weapons.size()]->isActive = true;
				return;
			}
		}
		weapons[0]->isActive = true;
	}
}
*/