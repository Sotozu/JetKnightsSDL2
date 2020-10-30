#include "Sound.h"


Sound::Sound() {
	workingDir = findWorkingDir();
	loadSound();
}

void Sound::loadSound()
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

	gLow = Mix_LoadWAV((workingDir + "/assets/sound/low.wav").c_str());
	if (gLow == NULL)
	{
		printf("Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	
	}
	gThruster = Mix_LoadMUS((workingDir + "/assets/sound/thrusterFire_004.wav").c_str());
	if (gThruster == NULL)
	{
		printf("Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError());

	}



}

void Sound::playgScratch() {
	Mix_PlayChannel(-1, gScratch, 0);
}
void Sound::playgHigh() {
	Mix_PlayChannel(-1, gHigh, 0);
}
void Sound::playgMedium() {
	Mix_PlayChannel(-1, gMedium, 0);
}
void Sound::playgLow() {
	Mix_PlayChannel(-1, gLow, 0);
}
void Sound::playgThruster() {
	Mix_PlayMusic(gThruster, -1);
}

Mix_Music* Sound::getThruster() {
	return gThruster;
}

std::string Sound::findWorkingDir() {
	char buf[256];
	GetCurrentDirectoryA(256, buf);
	return std::string(buf) + '\\';
}