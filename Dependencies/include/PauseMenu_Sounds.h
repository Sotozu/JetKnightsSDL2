#pragma once
#include <SDL_mixer.h>
#include <string>
#include <SDL.h>
#include <stdio.h>
#include <windows.h>

class PauseMenu_Sounds {

public:
	//Constructor
	PauseMenu_Sounds();

	void playPauseMenuButtonPress();

	void playPauseMusicTheme();

	void stopMusic();


private:
	void loadSound();

	std::string findWorkingDir();
	std::string workingDir;

	//The sound effects that will be used
	Mix_Chunk* pauseMenuButtonPress = NULL;
	Mix_Music* pauseTheme = NULL;


};
