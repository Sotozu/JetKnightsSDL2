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
#include "PauseMenu_Sounds.h"


class Pause_Menu {

public:
	//Constructors
	Pause_Menu(SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT);

	void updateObjects(float);
	void renderTransparentRect();
	void genTestPanel();
	void handleEvent(SDL_Event e);
	void playPauseTheme();
	void stopMusic();




private:
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	PauseMenu_Sounds pauseMenuMusic;
	static const int TOTAL_IMAGES = 1;

	SDL_Renderer* gRenderer;

	std::vector<std::string> pauseMenuPanelImagesDir;
	std::vector<std::string> pauseMenuMusicDir;

	std::string findWorkingDir();
	std::string workingDir;


	LTexture pauseMenuPanelImages[TOTAL_IMAGES];

	std::list<GameObject*> panel;

	// Mutators

	void loadMedia();

	



	template<class B>
	void updateRenders(B items) {
		for (auto item : items) {
			item->render();
		}
	}



};