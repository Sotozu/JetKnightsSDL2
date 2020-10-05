#include "NewWeapon.h"

/*
we need to 
*/

NewWeapon::NewWeapon() : GameObject() {
	gRenderer = NULL;
	texture = NULL;

	posX = 0;
	posY = 0;

	dirX = 0;
	dirY = 0;

	joyX = 0;
	joyY = 0;

	radius = 0;

	hitboxOffsetX = 0;
	hitboxOffsetY = 0;
}

NewWeapon::NewWeapon(int x, int y, float angle, SDL_Renderer* renderer) : GameObject(x, y, angle, renderer) {
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

	radius = 0;

}

NewWeapon::NewWeapon(int x, int y, float angle, SDL_Renderer* renderer, LTexture* ltexture) : GameObject(x, y, angle, renderer, ltexture) {
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

	radius = 40;
}
/*
What variables from base object GameObject be used here? How can we 
*/
void NewWeapon::handleEvent( SDL_Event e ) {
	if (e.type == SDL_CONTROLLERAXISMOTION) {	
		//Joystick input

		//If player 1 input
		if (e.caxis.which == 0) {
			if (e.caxis.axis == 2) {							//X axis motion
				joyX = e.caxis.value;
				if (!inDeadCircle()) {							//Outside of dead zone // abs(e.jaxis.value) > JOYSTICK_DEAD_ZONE
					dirX = e.caxis.value;
				}
			}
			else if (e.caxis.axis == 3) {						//Y axis motion
				joyY = e.caxis.value;
				if (!inDeadCircle()) {							//Outside of dead zone
					dirY = e.caxis.value;
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

	posX = posX + radius * cos(ang * M_PI/180);  //If posX is not the position of a robot then the weapon will fly across the screen
	posY = posY + radius * sin(ang * M_PI / 180);
	if (hitbox != NULL) {
		hitbox->setPos(posX, posY);
	}

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

void NewWeapon::setAllParameters(int x, int y, float angle, SDL_Renderer* renderer, LTexture* ltexture) {

	//NewWeapon variables
	joyX = 0;
	joyY = 0;

	dirX = 0;
	dirY = 0;

	radius = 40;

	//GameObject Variables
	posX = x;
	posY = y;
	ang = angle;
	renderer = gRenderer;
	texture = ltexture;
}
