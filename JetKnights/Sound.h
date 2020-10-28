#pragma once
#include <SDL_mixer.h>
#include <string>
#include <SDL.h>
#include <stdio.h>
#include <cmath>

class Sound {

public:
	//Constructor
	Sound();
	
	//Destructor
	

	//Accessor

	//Mutator

	//Process
	void playgScratch();
	void playgHigh();
	void playgMedium();
	void playgLow();
	void playgThruster();

	Mix_Music* getThruster();

private:
	void loadSound();

	//The sound effects that will be used
	Mix_Chunk* gScratch = NULL;
	Mix_Chunk* gHigh = NULL;
	Mix_Chunk* gMedium = NULL;
	Mix_Chunk* gLow = NULL;

	Mix_Music* gThruster = NULL;
};
