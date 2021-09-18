#include "Game.h"

//Default Constructor

Game::Game() {

	workingDir = "";
	SCREEN_HEIGHT = 0;
	SCREEN_WIDTH = 0;
	gRenderer = NULL;
	isPaused = false;
	gGameController0 = NULL;
	gGameController1 = NULL;

	//List of assets that we will be using in the game
	images = { "assets/images/robotrightnew.png",
				"assets/images/pistols.png",
				"assets/images/bullet.png",
				"assets/images/crate.png",
				"assets/images/minigun.png",
				"assets/images/cannonsmall.png" };


}

//Constructor
Game::Game(SDL_Renderer* renderer, int screenW, int screenH, 
	SDL_GameController* CONTROLLER0, SDL_GameController* CONTROLLER1) {

	workingDir = findWorkingDir();
	SCREEN_HEIGHT = screenH;
	SCREEN_WIDTH = screenW;
	gRenderer = renderer;
	isPaused = false;
	gGameController0 = CONTROLLER0;
	gGameController1 = CONTROLLER1;

	//List of assets that we will be using in the game
	images = { workingDir + "../Dependencies/assets/images/robotrightnew.png",
				workingDir + "../Dependencies/assets/images/pistols.png",
				workingDir + "../Dependencies/assets/images/bullet.png",
				workingDir + "../Dependencies/assets/images/crate.png",
				workingDir + "../Dependencies/assets/images/minigun.png",
				workingDir + "../Dependencies/assets/images/cannonsmall.png" };

	//List of sounds that we will be using in the game


	loadMedia();

	genTestArena();

	//genTestRobots();
	//genTestObstacles();
	//genTestWeapon()

}

//function to intilize for dynamiclly created game
void Game::initialize(SDL_Renderer* renderer, int screenW, int screenH, 
	SDL_GameController* CONTROLLER0, SDL_GameController* CONTROLLER1) {

	workingDir = findWorkingDir();
	SCREEN_HEIGHT = screenH;
	SCREEN_WIDTH = screenW;
	gRenderer = renderer;
	isPaused = false;
	gGameController0 = CONTROLLER0;
	gGameController1 = CONTROLLER1;

	//List of assets that we will be using in the game
	images = { workingDir + "../Dependencies/assets/images/robotrightnew.png",
				workingDir + "../Dependencies/assets/images/pistols.png",
				workingDir + "../Dependencies/assets/images/bullet.png",
				workingDir + "../Dependencies/assets/images/crate.png",
				workingDir + "../Dependencies/assets/images/minigun.png",
				workingDir + "../Dependencies/assets/images/cannonsmall.png" };

	//List of sounds that we will be using in the game


	loadMedia();

	genTestArena();
	
	//genTestRobots();
	//genTestObstacles();
	//genTestWeapon()

}

void Game::pauseGame(SDL_Event e) {
	/*
	for (auto robot : robots) {

		robot->robotPaused(e);
		robot->passOnEvent(e);
	}
	for (auto weapon : weapons) {
		if (weapon != NULL) {
			weapon->handleEvent(e);
		}
	}
	*/
}

void Game::unpauseGame() {
	/*
	for (auto robot : robots) {
		robot->robotUnpause();
	}
	*/
}


//Loads all the textures for the game
void Game::loadMedia() {
	for (int i = 0; i < TOTAL_IMAGES; ++i) {
		textures[i].loadFromFile(images[i], gRenderer);
	}
}



// Passes SDL events to classes that use them
void Game::handleEvent(SDL_Event e) {
	mainObj->handleEvent(e);
}

// Update order of the game
void Game::update(float timeStep) {
	mainObj->handleUpdate(timeStep);
}

/*
// Explicitly generates Robots
void Game::genTestRobots() {
	RelTexture* roboTex = new RelTexture(textures[0].getWidth() / -2, textures[0].getHeight() / -2, 0, &textures[0], gRenderer);
	RelTexture* wepTex = new RelTexture(textures[1].getWidth() / -2, textures[1].getHeight() / -2, 0, &textures[1], gRenderer);
	RelTexture* minigunTex = new RelTexture(textures[4].getWidth() / -2, textures[4].getHeight() / -2, 0, &textures[4], gRenderer);
	RelTexture* cannonTex = new RelTexture(textures[5].getWidth() / -2, textures[5].getHeight() / -2, 0, &textures[5], gRenderer);


	NewRobot* robot0 = new NewRobot(500, 500, 0, gRenderer, &*roboTex, gGameController0);
	robot0->addHitbox();
	robot0->team = 1;
	robot0->setPlayer(0);
	// Adding Weapon child
	NewWeapon* wep0 = new NewWeapon(0, 50, 0, gRenderer, &*wepTex);
	wep0->setParams(0, 50, true);
	robot0->addChild(*wep0);
	// Add second Weapon
	NewWeapon* wep01 = new NewWeapon(0, 50, 0, gRenderer, &*minigunTex);
	wep01->setParams(0, 10, false);
	robot0->addChild(*wep01);
	// Add third Weapon
	NewWeapon* wep02 = new NewWeapon(0, 50, 0, gRenderer, &*cannonTex);
	wep02->setParams(0, 250, false);
	robot0->addChild(*wep02);
	// Add robot to robot list
	mainObj->addChild(robot0);

	NewRobot* robot1 = new NewRobot(450, 325, 0, gRenderer, &*roboTex, gGameController1);
	robot1->addHitbox();
	robot1->team = 2;
	robot1->setPlayer(1);
	// Adding Weapon child
	NewWeapon* wep00 = new NewWeapon(0, 50, 0, gRenderer, &*wepTex);
	wep00->setParams(1, 50, true);
	robot1->addChild(*wep00);
	// Add second Weapon
	NewWeapon* wep11 = new NewWeapon(0, 50, 0, gRenderer, &*minigunTex);
	wep11->setParams(1, 10, false);
	robot1->addChild(*wep11);
	// Add third Weapon
	NewWeapon* wep22 = new NewWeapon(0, 50, 0, gRenderer, &*cannonTex);
	wep22->setParams(1, 250, false);
	robot1->addChild(*wep22);
	// Add robot to robot list
	mainObj->addChild(robot1);
	
	// Creating Status Bars
	StatusBar* health_bar1 = new StatusBar(25, 25, &robot1->health, gRenderer);
	mainObj->addChild(health_bar1);
	StatusBar* health_bar2 = new StatusBar(SCREEN_WIDTH - 25, 25, &robot0->health, gRenderer);
	health_bar2->reverse();
	mainObj->addChild(health_bar2);

}

// Progressively generates bullets and play sound for when one is generated
void Game::genTestBullets(NewWeapon* weapon) {
	RelTexture* bulletTex = new RelTexture(textures[2].getWidth() / -2, textures[2].getHeight() / -2, 0, &textures[2], gRenderer);
	Bullet* new_bullet = new Bullet(weapon->getPosX(), weapon->getPosY(), weapon->getAngle(), 1200, gRenderer, &*bulletTex);
	new_bullet->addHitbox();
	new_bullet->setTeam(weapon->team);
	mainObj->addChild(new_bullet);

	//play weapon sound
	weapon->weaponSound();
}

// Explicitly generates obstacles
void  Game::genTestObstacles() {
	RelTexture* crateTex = new RelTexture(0, 0, 0, &textures[3], gRenderer);

	GameObject* obstacle0 = new GameObject(300, 300, 0, gRenderer, &*crateTex);
	obstacle0->addHitbox();
	mainObj->addChild(obstacle0);

	GameObject* obstacle1 = new GameObject(600, 100, 0, gRenderer, &*crateTex);
	obstacle1->addHitbox();
	mainObj->addChild(obstacle1);
}
*/

void Game::genTestArena() {
	Arena* p_arena = new Arena();
	
	addObstacle(p_arena, 100, 100);
	addObstacle(p_arena, 300, 100);

	addRobot(p_arena, 100, 300);

	mainObj = p_arena;
}

void Game::addObstacle(IGameObject* parent, float m_x, float m_y) {
	Obstacle* p_obstalce = new Obstacle(m_x, m_y, 0);
	p_obstalce->addDefaultHitbox();
	parent->addChild(p_obstalce);
}

void Game::addRobot(IGameObject* parent, float m_x, float m_y) {
	NewRobot* robot = new NewRobot(m_x, m_y, 0, nullptr);
	//robot->addHitbox();
	robot->team = 1;
	robot->setPlayer(0);
	robot->addDefaultHitbox();

	parent->addChild(robot);
}

std::string Game::findWorkingDir() {
	char buf[256];
	GetCurrentDirectoryA(256, buf);
	return std::string(buf) + '\\';
}

void Game::playFightTheme() {
	soundEffects.playFightTheme();
}

void Game::playMenuTheme() {
	soundEffects.playMenuTheme();
}

void Game::playPauseTheme() {
	soundEffects.playPauseTheme();
}

void Game::stopMusic() {
	soundEffects.stopMusic();
}
