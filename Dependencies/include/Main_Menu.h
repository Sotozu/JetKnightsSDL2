#pragma once

#include <list>
#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <SDL_gamecontroller.h>
#include <iomanip>
#include <SDL_mixer.h>
#include <windows.h>
#include <variant>

#include "GameObject.h"
#include "RelTexture.h"
#include "MainMenu_Sounds.h"


class Main_Menu {
public:
	//Constructors
	Main_Menu(SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT);

	void updateObjects(float);

	void genTestPanel();
	void handleEvent(SDL_Event e);

	void playMainMenuTheme();
	void stopMusic();


private:
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;

	MainMenu_Sounds mainMenuMusic;

	static const int TOTAL_IMAGES = 1;

	SDL_Renderer* gRenderer;

	std::vector<std::string> menuBackgroundImagesDir;
	std::vector<std::string> pauseMenuMusicDir;


	LTexture menuBackgroundImages[TOTAL_IMAGES];

	std::list<GameObject*> panel;

	// Mutators

	void loadMedia();

	std::string findWorkingDir();
	std::string workingDir;


	template<class B>
	void updateRenders(B items) {
		for (auto item : items) {
			item->render();
		}
	}

};