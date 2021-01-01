#include "PauseMenu_Sounds.h"


PauseMenu_Sounds::PauseMenu_Sounds() {
	workingDir = findWorkingDir();
	loadSound();
}

void PauseMenu_Sounds::loadSound()
{

	//Loading success flag
	bool success = true;


	//Load sound effects
	pauseMenuButtonPress = Mix_LoadWAV((workingDir + "../Dependencies/assets/sound/scratch.wav").c_str());
	if (pauseMenuButtonPress == NULL)
	{
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());

	}

	pauseTheme = Mix_LoadMUS((workingDir + "../Dependencies/assets/sound/pause_menu.wav").c_str());
	if (pauseTheme == NULL)
	{
		printf("Failed to load fightTheme sound effect! SDL_mixer Error: %s\n", Mix_GetError());

	}



}

void PauseMenu_Sounds::playPauseMenuButtonPress() {
	Mix_PlayChannel(-1, pauseMenuButtonPress, 0);
}

void PauseMenu_Sounds::playPauseMusicTheme() {
	Mix_PlayMusic(pauseTheme, -1);
}
void PauseMenu_Sounds::stopMusic() {
	Mix_HaltMusic();
}


std::string PauseMenu_Sounds::findWorkingDir() {
	char buf[256];
	GetCurrentDirectoryA(256, buf);
	return std::string(buf) + '\\';
}