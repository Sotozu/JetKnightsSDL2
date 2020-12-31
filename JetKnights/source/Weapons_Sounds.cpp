#include "Weapon_Sounds.h"


Weapon_Sounds::Weapon_Sounds() {
	workingDir = findWorkingDir();
	loadSound();
}

void Weapon_Sounds::loadSound()
{

	//Loading success flag
	bool success = true;


	//Load sound effects
	gScratch = Mix_LoadWAV((workingDir + "/assets/sound/scratch.wav").c_str());
	if (gScratch == NULL)
	{
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());

	}

	gHigh = Mix_LoadWAV((workingDir + "/assets/sound/high.wav").c_str());
	if (gHigh == NULL)
	{
		printf("Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError());

	}

	gMedium = Mix_LoadWAV((workingDir + "/assets/sound/medium.wav").c_str());
	if (gMedium == NULL)
	{
		printf("Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError());

	}

	gLow = Mix_LoadWAV((workingDir + "/assets/sound/cat_meow.wav").c_str());
	std::cout << workingDir << std::endl;
	if (gLow == NULL)
	{
		
		printf("Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError());

	}

}

void Weapon_Sounds::playgScratch() {
	Mix_PlayChannel(-1, gScratch, 0);
}
void Weapon_Sounds::playgHigh() {
	Mix_PlayChannel(-1, gHigh, 0);
}
void Weapon_Sounds::playgMedium() {
	Mix_PlayChannel(-1, gMedium, 0);
}
void Weapon_Sounds::playgLow() {
	Mix_PlayChannel(-1, gLow, 0);
}



std::string Weapon_Sounds::findWorkingDir() {
	char buf[256];
	GetCurrentDirectoryA(256, buf);
	return std::string(buf) + '\\';
}