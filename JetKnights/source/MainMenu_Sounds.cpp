#include "MainMenu_Sounds.h"


MainMenu_Sounds::MainMenu_Sounds() {
	workingDir = findWorkingDir();
	loadSound();
}

void MainMenu_Sounds::loadSound()
{

	//Loading success flag
	bool success = true;


	//Load sound effects
	mainMenuButtonPress = Mix_LoadWAV((workingDir + "../Dependencies/assets/sound/scratch.wav").c_str());
	if (mainMenuButtonPress == NULL)
	{
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());

	}

	mainMenuTheme = Mix_LoadMUS((workingDir + "../Dependencies/assets/sound/main_menu.wav").c_str());
	if (mainMenuTheme == NULL)
	{
		printf("Failed to load fightTheme sound effect! SDL_mixer Error: %s\n", Mix_GetError());

	}



}

void MainMenu_Sounds::playMainMenuButtonPress() {
	Mix_PlayChannel(-1, mainMenuButtonPress, 0);
}

void MainMenu_Sounds::playMainMenuMusicTheme() {
	Mix_PlayMusic(mainMenuTheme, -1);
}
void MainMenu_Sounds::stopMusic() {
	Mix_HaltMusic();
}


std::string MainMenu_Sounds::findWorkingDir() {
	char buf[256];
	GetCurrentDirectoryA(256, buf);
	return std::string(buf) + '\\';
}