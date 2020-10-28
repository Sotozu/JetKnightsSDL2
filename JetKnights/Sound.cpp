#include "Sound.h"


Sound::Sound() {
	loadSound();
}

void Sound::loadSound()
{

	//Loading success flag
	bool success = true;
	

	//Load sound effects
	gScratch = Mix_LoadWAV("C:/source/JetKnights/JetKnights/assets/sound/scratch.wav");
	if (gScratch == NULL)
	{
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	
	}

	gHigh = Mix_LoadWAV("C:/source/JetKnights/JetKnights/assets/sound/high.wav");
	if (gHigh == NULL)
	{
		printf("Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError());

	}

	gMedium = Mix_LoadWAV("C:/source/JetKnights/JetKnights/assets/sound/medium.wav");
	if (gMedium == NULL)
	{
		printf("Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	
	}

	gLow = Mix_LoadWAV("C:/source/JetKnights/JetKnights/assets/sound/low.wav");
	if (gLow == NULL)
	{
		printf("Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	
	}
	gThruster = Mix_LoadMUS("C:/source/JetKnights/JetKnights/assets/sound/thrusterFire_004.wav");
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