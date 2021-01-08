#pragma once
#include <SDL_mixer.h>
#include <string>
#include <SDL.h>
#include <stdio.h>
#include <windows.h>

class MainMenu_Sounds {

public:
	//Constructor
	MainMenu_Sounds();

	void playMainMenuButtonPress();

	void playMainMenuMusicTheme();

	void stopMusic();


private:
	void loadSound();

	std::string findWorkingDir();
	std::string workingDir;

	//The sound effects that will be used
	Mix_Chunk* mainMenuButtonPress = NULL;
	Mix_Music* mainMenuTheme = NULL;


};
