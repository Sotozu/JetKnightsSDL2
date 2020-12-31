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
				"assets/images/cannonsmall.png",
				"assets/images/bullet-2.png",
				"assets/images/crate.png" };


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
	images = { "assets/images/robotrightnew.png",
				"assets/images/pistols.png",
				"assets/images/bullet-2.png",
				"assets/images/crate.png",
				"assets/images/minigun.png",
				"assets/images/cannonsmall.png" };

	//List of sounds that we will be using in the game


	loadMedia();

	genTestRobots();
	genTestObstacles();
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
	images = { "assets/images/robotrightnew.png",
				"assets/images/pistols.png",
				"assets/images/bullet-2.png",
				"assets/images/crate.png",
				"assets/images/minigun.png",
				"assets/images/cannonsmall.png" };

	//List of sounds that we will be using in the game


	loadMedia();

	genTestRobots();
	genTestObstacles();
	//genTestWeapon()

}

void Game::pauseGame(SDL_Event e) {


	for (auto robot : robots) {

		robot->pauseRobot();

		robot->handleEvent(e);
		robot->passOnEvent(e);
	}
	for (auto weapon : weapons) {
		if (weapon != NULL) {
			weapon->handleEvent(e);
		}
	}
}

//Loads all the textures for the game
void Game::loadMedia() {
	for (int i = 0; i < TOTAL_IMAGES; ++i) {
		textures[i].loadFromFile(images[i], gRenderer);
	}
}



// Passes SDL events to classes that use them
void Game::handleEvent(SDL_Event e) {
	for (auto robot : robots) {

		robot->unpauseRobot();
		robot->handleEvent(e);
		robot->passOnEvent(e);
	}
	for (auto weapon : weapons) {
		if (weapon != NULL) {
			weapon->handleEvent(e);
		}
	}
}

// Update order of the game
void Game::updateObjects(float timeStep) {

	//---MOVE ALL OBJECTS---
	//updateMovements(robots, timeStep);

	updateRobotMovements(robots, timeStep);

	updateMovements(weapons, timeStep);
	updateMovements(bullets, timeStep);

	//---COLLIDE ALL OBJECTS---
	updateRobotBulletCollisions(robots, bullets, timeStep);
	updateAllCollisions(bullets, timeStep);
	
	//---SPAWN NEW OBJECTS---

	//spawnBullets();

	for (auto robot : robots) {
		spawnBulletsRecursive(*robot);
	}
	
	//---Render All OBJECTS---
	updateRenders(robots);
	updateRenders(weapons);
	updateRenders(bullets);
	updateRenders(obstacles);

	//---UPDATE VISUALS---
	for (auto item : bars) {
		item->update();
		item->render();
	}

	//---DESPAWN DEAD OBJECTS---
	despawn(&robots);
	despawn(&bullets);
	despawn(&weapons);

	//--cout info--

}

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
	wep02->setParams(0, 150, false);
	robot0->addChild(*wep02);
	// Add robot to robot list
	robots.push_back(robot0);

	NewRobot* robot1 = new NewRobot(450, 325, 0, gRenderer, &*roboTex, gGameController1);
	robot1->addHitbox();
	robot1->team = 2;
	robot1->setPlayer(1);
	// Adding Weapon child
	NewWeapon* wep1 = new NewWeapon(0, 50, 0, gRenderer, &*wepTex);
	wep1->setPlayer(1);
	robot1->addChild(*wep1);
	robots.push_back(robot1);
	
	// Creating Status Bars
	StatusBar* health_bar1 = new StatusBar(25, 25, &robot1->health, gRenderer);
	bars.push_back(health_bar1);
	StatusBar* health_bar2 = new StatusBar(SCREEN_WIDTH - 25, 25, &robot0->health, gRenderer);
	health_bar2->reverse();
	bars.push_back(health_bar2);

}

// Progressively generates bullets and play sound for when one is generated
void Game::genTestBullets(NewWeapon* weapon) {
	RelTexture* bulletTex = new RelTexture(textures[2].getWidth() / -2, textures[2].getHeight() / -2, 0, &textures[2], gRenderer);
	Bullet* new_bullet = new Bullet(weapon->getPosX(), weapon->getPosY(), weapon->getAngle(), 1200, gRenderer, &*bulletTex);
	new_bullet->addHitbox();
	new_bullet->setTeam(weapon->team);
	bullets.push_back(new_bullet);

	//play weapon sound
	weapon->weaponSound();
}

// Explicitly generates obstacles
void  Game::genTestObstacles() {
	RelTexture* crateTex = new RelTexture(0, 0, 0, &textures[3], gRenderer);

	GameObject* obstacle0 = new GameObject(300, 300, 0, gRenderer, &*crateTex);
	obstacle0->addHitbox();
	obstacles.push_back(obstacle0);

	GameObject* obstacle1 = new GameObject(600, 100, 0, gRenderer, &*crateTex);
	obstacle1->addHitbox();
	obstacles.push_back(obstacle1);
}


// Updates entire robot array by checking if they collide with bullets

void Game::updateRobotBulletCollisions(std::list<NewRobot*> robotlist, std::list<Bullet*> bulletlist, float timeStep) {
	for (auto robot : robotlist) { //iterate through each robot, and for each robot...
		for (auto bullet : bulletlist) {//iterate through each bullet in the game
			robot->updateCollision(bullet, timeStep);
		}
	}
}

void Game::updateAllRobotCollisionsX(std::list<NewRobot*> robotlist, float timeStep) {
	for (auto robot : robotlist) {
		robot->updateBorderCollision(SCREEN_WIDTH, SCREEN_HEIGHT, timeStep);

		updateCollisionsX(robot, robots, timeStep);

		updateCollisionsX(robot, obstacles, timeStep);

	}
}

void Game::updateAllRobotCollisionsY(std::list<NewRobot*> robotlist, float timeStep) {
	for (auto robot : robotlist) {
		robot->updateBorderCollision(SCREEN_WIDTH, SCREEN_HEIGHT, timeStep);

		updateCollisionsY(robot, robots, timeStep);

		updateCollisionsY(robot, obstacles, timeStep);
	}
}

// Updates entire bullet array by checking thigs they collide with
void Game::updateAllCollisions(std::list<Bullet*> mybullets, float timeStep) {
	for (auto bullet : bullets) {
		bullet->updateBorderCollision(SCREEN_WIDTH, SCREEN_HEIGHT);
		updateCollisions(bullet, robots, timeStep);
		updateCollisions(bullet, obstacles, timeStep);
	}
}

// Checks if a weapon is firing and spawns a bullet
//void Game::spawnBullets() {
//	for (auto weapon : weapons) {
//		if (weapon->isFiring && weapon->canFire() && weapon->isActive) {
//			weapon->attemptToFire();
//			genTestBullets(weapon);
//		}
//	}
//}

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
