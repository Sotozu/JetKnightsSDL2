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
	player = 0;
	isFiring = false;
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
	player = 0;
	isFiring = false;

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
				std::cout << e.caxis.value << std::endl;
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


void NewWeapon::update() {
	ang = getAngle();

	posX = static_cast<int>(round(posX + radius * cos(ang * M_PI / 180)));  //If posX is not the position of a robot then the weapon will fly across the screen
	posY = static_cast<int>(round(posY + radius * sin(ang * M_PI / 180)));
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

//bool NewWeapon::WeaponFiring(SDL_Event e) {
//	//Handle Bullet Creation
//	static int num = 0;
//
//	
//	if (e.type == SDL_CONTROLLERAXISMOTION) {
//		//Joystick input
//
//		//If player 1 input
//		if (e.caxis.which == player) {
//
//			if (e.caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERRIGHT) {
//				//std::cout << "WHAT!!!" << std::endl;
//				//std::cout << e.caxis.value << std::endl;
//				if (e.caxis.value > 5000) {
//					//std::cout << "Greater than 5000: " << e.caxis.value << std::endl;
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
//	else if (num > 5000) {
//		return true;
//	}
//	else {
//		return false;
//	}
//}

void NewWeapon::setPlayer(int a) {
	player = a;
}