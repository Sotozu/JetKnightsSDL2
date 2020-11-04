#include "ThemeMusic.h"


ThemeMusic::ThemeMusic() {
	workingDir = findWorkingDir();
	loadThemeMusic();
}

void ThemeMusic::loadThemeMusic()
{

	//Loading success flag
	bool success = true;

	//Load ThemeMusic

	fightTheme = Mix_LoadMUS((workingDir + "/assets/sound/fight_sound_track.wav").c_str());
	if (fightTheme == NULL)
	{
		printf("Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError());

	}



}

void ThemeMusic::playFightTheme() {
	Mix_PlayMusic(fightTheme, -1);
}

Mix_Music* ThemeMusic::getFightTheme() {
	return fightTheme;
}

std::string ThemeMusic::findWorkingDir() {
	char buf[256];
	GetCurrentDirectoryA(256, buf);
	return std::string(buf) + '\\';
}