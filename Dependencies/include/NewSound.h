#pragma once
#include <SDL_mixer.h>
#include <string>
#include <SDL.h>
#include <stdio.h>
#include <windows.h>
#include <vector>
#include <list>



class NewSound {

public:
	//Default Constructor
	NewSound();

	NewSound(std::list<std::string> soundDirList);

	//Destructor


	//Accessor

	//Mutator

	//Process
	void playgScratch();
	void playgHigh();
	void playgMedium();
	void playgLow();
	void turnThrusterOn();
	void turnThrusterOff();

	void playFightTheme();
	void playPauseTheme();
	void playMenuTheme();

	void stopMusic();


private:
	void loadSound();

	std::string findWorkingDir();
	std::string workingDir;

	//list of sound effect file paths
	std::list<std::string> soundEffectFileList;

	//list of music file paths
	std::list<std::string> musicFileList;

	//list of sound effects
	std::list<Mix_Chunk*> soundEffectList;
	
	//list of music
	std::list<Mix_Music*> musicList;



	//The sound effects that will be used
	Mix_Chunk* gScratch = NULL;
	Mix_Chunk* gHigh = NULL;
	Mix_Chunk* gMedium = NULL;
	Mix_Chunk* gLow = NULL;
	Mix_Chunk* thrusterOn = NULL;
	Mix_Chunk* thrusterPowerDown = NULL;

	Mix_Music* fightTheme = NULL;
	Mix_Music* pauseTheme = NULL;
	Mix_Music* menuTheme = NULL;


};
