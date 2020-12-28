#pragma once
#include <SDL_mixer.h>
#include <string>
#include <SDL.h>
#include <stdio.h>
#include <windows.h>

class Weapon_Sounds {

public:
	//Constructor
	Weapon_Sounds();

	//Destructor


	//Accessor

	//Mutator

	//Process
	void playgScratch();
	void playgHigh();
	void playgMedium();
	void playgLow();
	


private:
	void loadSound();

	std::string findWorkingDir();
	std::string workingDir;

	//The sound effects that will be used
	Mix_Chunk* gScratch = NULL;
	Mix_Chunk* gHigh = NULL;
	Mix_Chunk* gMedium = NULL;
	Mix_Chunk* gLow = NULL;



};
