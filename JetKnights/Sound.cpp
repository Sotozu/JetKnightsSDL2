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
	thrusterOn = Mix_LoadWAV((workingDir + "/assets/sound/thrusterFire.wav").c_str());
	if (thrusterOn == NULL)
	{
		printf("Failed to load thrusterOn effect! SDL_mixer Error: %s\n", Mix_GetError());

	}
	thrusterPowerDown = Mix_LoadWAV((workingDir + "/assets/sound/thrusterPowerDown1.wav").c_str());
	if (thrusterPowerDown == NULL)
	{
		printf("Failed to load thrusterPowerDown sound effect! SDL_mixer Error: %s\n", Mix_GetError());

	}
	fightTheme = Mix_LoadMUS((workingDir + "/assets/sound/fight_sound_track.wav").c_str());
	if (fightTheme == NULL)
	{
		printf("Failed to load fightTheme sound effect! SDL_mixer Error: %s\n", Mix_GetError());

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
void Sound::turnThrusterOn() {
	Mix_PlayChannel(1, thrusterOn, 0);
}
void Sound::turnThrusterOff() {
	Mix_HaltChannel(1);
	Mix_PlayChannel(-1, thrusterPowerDown, 0);
}
void Sound::playFightTheme() {
	Mix_PlayMusic(fightTheme, -1);
}
void Sound::stopFightTheme() {
	Mix_HaltMusic();
}


std::string Sound::findWorkingDir() {
	char buf[256];
	GetCurrentDirectoryA(256, buf);
	return std::string(buf) + '\\';
}