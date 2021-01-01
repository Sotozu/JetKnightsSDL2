#include "Main_Menu.h"


//Constructor
Main_Menu::Main_Menu(SDL_Renderer* renderer, int screenW, int screenH) {

	SCREEN_HEIGHT = screenH;
	SCREEN_WIDTH = screenW;
	gRenderer = renderer;
	workingDir = findWorkingDir();

	//List of assets that we will be using in the game
	menuBackgroundImagesDir = { workingDir + "../Dependencies/assets/images/Main_Menu.jpg" };


	//List of sounds that we will be using in the game


	loadMedia();

	genTestPanel();
}

//Loads all the textures for the game
void Main_Menu::loadMedia() {
	for (int i = 0; i < TOTAL_IMAGES; ++i) {
		menuBackgroundImages[i].loadFromFile(menuBackgroundImagesDir[i], gRenderer);
		//soundEffects[i].loadSound(sounds[i]);
	}
}



// Passes SDL events to classes that use them
void Main_Menu::handleEvent(SDL_Event e) {

	/*for (auto robot : robots) {
		robot->handleEvent(e);
		robot->passOnEvent(e);
	}
	for (auto weapon : weapons) {
		if (weapon != NULL) {
			weapon->handleEvent(e);
		}
	}*/

}

// Update order of the game


void Main_Menu::updateObjects(float timeStep) {
	updateRenders(panel);
}

/*SHOULD GENERATE MENU TEMPLATE AND FILL WITH BUTTONS*/


void  Main_Menu::genTestPanel () {

	RelTexture* panelTex = new RelTexture(0, 0, 0, &menuBackgroundImages[0], gRenderer);

	GameObject* panel0 = new GameObject(0, 0, 0, gRenderer, &*panelTex);
	panel0->addHitbox();
	panel.push_back(panel0);

}

	std::string Main_Menu::findWorkingDir() {
		char buf[256];
		GetCurrentDirectoryA(256, buf);
		return std::string(buf) + '\\';
	}
