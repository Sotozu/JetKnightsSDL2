#include "NewWeapon.h"

NewWeapon::NewWeapon() : GameObject() {
	joyX = 0;
	joyY = 0;

	dirX = 0;
	dirY = 0;

	radius = 0;
	player = 0;
	isFiring = false;
	bulletInterval = 50;

	stepTimer.start();
}

NewWeapon::NewWeapon(int m_x, int m_y, float angle, SDL_Renderer* renderer) : GameObject(m_x, m_y, angle, renderer) {
	
	//'joyX' and 'joyY' hold the all the value of the joystick +-320000
	joyX = 0;
	joyY = 0;

	//Hold the x and y values of the joystick only outside of the deadzone.
	dirX = 0;
	dirY = 0;

	radius = 0;
	player = 0;
	isFiring = false;
	bulletInterval = 50;

	stepTimer.start();
}

NewWeapon::NewWeapon(int m_x, int m_y, float angle, SDL_Renderer* renderer, RelTexture* texture) : GameObject(m_x, m_y, angle, renderer, texture) {

	//'joyX' and 'joyY' hold the all the value of the joystick +-320000
	joyX = 0;
	joyY = 0;

	//Hold the x and y values of the joystick only outside of the deadzone.
	dirX = 0;
	dirY = 0;

	radius = 40;
	player = 0;
	isFiring = false;
	bulletInterval = 50;

	stepTimer.start();
}

void NewWeapon::onEventJoyX(SDL_Event e) {
	if (e.caxis.axis == 2) {
		joyX = e.caxis.value;
		if (!inDeadCircle()) {
			dirX = e.caxis.value;
		}
	}
}

void NewWeapon::onEventJoyY(SDL_Event e) {
	if (e.caxis.axis == 3) {
		joyY = e.caxis.value;
		if (!inDeadCircle()) {
			dirY = e.caxis.value;
		}
	}
}

void NewWeapon::onRightTriggerEvent(SDL_Event e) {
	if (e.caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERRIGHT) {
		if (e.caxis.value > TRIGGER_DEAD_ZONE) {
			isFiring = true;
		}
		else {
			isFiring = false;
		}
	}
}

// How the weapon handles SDL events
void NewWeapon::handleEvent( SDL_Event e ) {
	//Joystick input
	if (e.type == SDL_CONTROLLERAXISMOTION) {
		//If event matches player
		if (e.caxis.which == player) {
			//X axis motion
			onEventJoyX(e);
			//Y axis motion
			onEventJoyY(e);
			//Right Trigger press
			onRightTriggerEvent(e);
		}
	}
}

float NewWeapon::getAngle() {
	//Calculate angle
	float joyAngle = static_cast<float>(atan2((double)dirY, (double)dirX) * (180.0 / M_PI));
	return joyAngle;
}

int NewWeapon::getJoyX() {
	return joyX;
}

int NewWeapon::getJoyY() {
	return joyY;
}


void NewWeapon::update(float timestep) {
	ang = getAngle();
	relX = static_cast<int>(round(radius * cos(ang * M_PI / 180)));
	relY = static_cast<int>(round(radius * sin(ang * M_PI / 180)));
	updatePos();
}

bool NewWeapon::canFire() {
	return (stepTimer.getTicks() >= bulletInterval);
}

void NewWeapon::attemptToFire() {
	if (canFire()) {
		stepTimer.start();
	}
}

//Calculates a dead zone circle as opposed to dead zone cross
bool NewWeapon::inDeadCircle() {
	if (JOYSTICK_DEAD_ZONE > sqrt(pow(joyX, 2) + pow(joyY, 2))) {
		return true;
	}
	else {
		return false;
	}
}

void NewWeapon::setAllParameters(int m_x, int m_y, float angle, SDL_Renderer* renderer, RelTexture* texture) {

	//NewWeapon variables
	joyX = 0;
	joyY = 0;

	dirX = 0;
	dirY = 0;

	radius = 40;

	//GameObject Variables
	posX = m_x;
	posY = m_y;
	ang = angle;
	renderer = gRenderer;
	textures.push_back(*texture);
}

void NewWeapon::setPlayer(int a) {
	player = a;
}

void NewWeapon::weaponSound() {
	weaponSounds.playgLow();
}

void NewWeapon::setBulletInterval(int value) {
	bulletInterval = value;
}

void NewWeapon::setParams(int player, int interval, bool isActive) {
	this->player = player;
	bulletInterval = interval;
	this->isActive = isActive;
}
