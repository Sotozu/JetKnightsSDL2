#pragma once

#include <SDL_mixer.h>
#include <string>
#include <SDL.h>
#include <stdio.h>
#include <windows.h>
#include <iostream>

class ThemeMusic {

public:
	//Constructor
	ThemeMusic();

	//Destructor


	//Accessor

	//Mutator

	//Process
	
	void playFightTheme();

	Mix_Music* getFightTheme();

private:
	void loadThemeMusic();

	std::string findWorkingDir();
	std::string workingDir;

	//The theme music that will be used

	Mix_Music* fightTheme = NULL;


};
