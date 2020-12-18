#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>


class Controller {


	
public:

	//Constructor
	Controller();

	//Destructor


	//Accessor


	//Mutators


private:
	SDL_Joystick* GameController;
	const int JOYSTICK_DEAD_ZONE = 8000;
	

};