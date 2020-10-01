#include "NewWeapon.h"

NewWeapon::NewWeapon() {
	gRenderer = NULL;
	texture = NULL;
	hitbox = Hitbox();
	posX = 0;
	posY = 0;
	ang = 0;
	hitboxOffsetX = 0;
	hitboxOffsetY = 0;
}

NewWeapon::NewWeapon(int x, int y, float angle, SDL_Renderer* renderer) : GameObject(x, y, angle, renderer) {	
	joyX = 0;
	joyY = 0;
	dirX = 0;
	dirY = 0;
	radius = 40;
	cenX = posX;
	cenY = posY;
}

void NewWeapon::handleEvent( SDL_Event e ) {
	if (e.type == SDL_JOYAXISMOTION) {							//Joystick input
		if (e.jaxis.which == 0) {								//If player 1 input
			if (e.jaxis.axis == 0) {							//X axis motion
				joyX = e.jaxis.value;
				if (!inDeadCircle()) {							//Outside of dead zone // abs(e.jaxis.value) > JOYSTICK_DEAD_ZONE
					dirX = e.jaxis.value;
				}
			}
			else if (e.jaxis.axis == 1) {						//Y axis motion
				joyY = e.jaxis.value;
				if (!inDeadCircle()) {							//Outside of dead zone
					dirY = e.jaxis.value;
				}
			}
		}
	}	
}

float NewWeapon::getAngle() {
	//Calculate angle
	double joyAngle = atan2((double)dirY, (double)dirX) * (180.0 / M_PI);
	return joyAngle;
}

int NewWeapon::getJoyX() {
	return joyX;
}

int NewWeapon::getJoyY() {
	return joyY;
}


void NewWeapon::update() {
	ang = getAngle();
	//std::cout << joyY << std::endl;
	posX = cenX + radius * cos(ang * M_PI/180);
	posY = cenY + radius * sin(ang * M_PI / 180);
}

bool NewWeapon::inDeadCircle() {
	//Calculates a dead zone circle as opposed to dead zone cross
	if (JOYSTICK_DEAD_ZONE > sqrt(pow(joyX, 2) + pow(joyY, 2))) {
		return true;
	}
	else {
		return false;
	}
}

