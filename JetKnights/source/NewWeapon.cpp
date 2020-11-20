#include "NewWeapon.h"

/*
we need to 
*/

NewWeapon::NewWeapon() : GameObject() {
	joyX = 0;
	joyY = 0;

	dirX = 0;
	dirY = 0;

	radius = 0;
	player = 0;
	isFiring = false;
}

NewWeapon::NewWeapon(int x, int y, float angle, SDL_Renderer* renderer) : GameObject(x, y, angle, renderer) {
	
	//'joyX' and 'joyY' hold the all the value of the joystick +-320000
	joyX = 0;
	joyY = 0;

	//Hold the x and y values of the joystick only outside of the deadzone.
	dirX = 0;
	dirY = 0;

	radius = 0;
	player = 0;
	isFiring = false;

}

NewWeapon::NewWeapon(int x, int y, float angle, SDL_Renderer* renderer, LTexture* ltexture) : GameObject(x, y, angle, renderer, ltexture) {

	//'joyX' and 'joyY' hold the all the value of the joystick +-320000
	joyX = 0;
	joyY = 0;

	//Hold the x and y values of the joystick only outside of the deadzone.
	dirX = 0;
	dirY = 0;

	radius = 40;
	player = 0;
	isFiring = false;
}

// How the weapon handles SDL events
void NewWeapon::handleEvent( SDL_Event e ) {
	//Joystick input
	if (e.type == SDL_CONTROLLERAXISMOTION) {	
		//If event matches player
		if (e.caxis.which == player) {
			//X axis motion
			if (e.caxis.axis == 2) {						
				joyX = e.caxis.value;
				if (!inDeadCircle()) {						
					dirX = e.caxis.value;
				}
			}
			//Y axis motion
			else if (e.caxis.axis == 3) {
				joyY = e.caxis.value;
				if (!inDeadCircle()) {	
					dirY = e.caxis.value;
				}
			}
			//Trigger press
			else if (e.caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERRIGHT) {
				if (e.caxis.value > TRIGGER_DEAD_ZONE) {
					isFiring = true;
				}
				else {
					isFiring = false;
				}
			}
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

	//again this relX buisness is a dirty way to get relative objects
	if (relXp != NULL && relYp != NULL) {
		posX = static_cast<int>(round(*relXp + radius * cos(ang * M_PI / 180)));
		posY = static_cast<int>(round(*relYp + radius * sin(ang * M_PI / 180)));
	}
	else {
		posX = static_cast<int>(round(radius * cos(ang * M_PI / 180)));
		posY = static_cast<int>(round(radius * sin(ang * M_PI / 180)));
	}
	for( auto hitbox : hitboxes ) {
		hitbox.setPos(posX, posY);
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
	textures.push_back(*ltexture);
}

void NewWeapon::setPlayer(int a) {
	player = a;
}