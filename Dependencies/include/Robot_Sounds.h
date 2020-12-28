#pragma once
#include <SDL_mixer.h>
#include <string>
#include <SDL.h>
#include <stdio.h>
#include <windows.h>

class Robot_Sounds {

public:
	//Constructor
	Robot_Sounds();

	void turnThrusterOn();
	void turnThrusterOff();


private:
	void loadSound();

	std::string findWorkingDir();
	std::string workingDir;


	Mix_Chunk* thrusterOn = NULL;
	Mix_Chunk* thrusterPowerDown = NULL;


};
