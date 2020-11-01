#include "Game.h"


//Constructor
Game::Game(SDL_Renderer* renderer, int screenW, int screenH) {

	workingDir = findWorkingDir();
	SCREEN_HEIGHT = screenH;
	SCREEN_WIDTH = screenW;
	gRenderer = renderer;

	//List of assets that we will be using in the game
	images = { workingDir + "/assets/images/robotrightnew.png",
				 workingDir + "/assets/images/cannonsmall.png",
				 workingDir + "/assets/images/bullet-2.png",
				workingDir + "/assets/images/crate.png" };

	//List of sounds that we will be using in the game


	loadMedia();

	genTestRobots();
	genTestObstacles();
	genTestWeapon();


}

//Loads all the textures for the game
void Game::loadMedia() {
	for (int i = 0; i < TOTAL_IMAGES; ++i) {
		textures[i].loadFromFile(images[i], gRenderer);
		//soundEffects[i].loadSound(sounds[i]);
	}
}



// Passes SDL events to classes that use them
void Game::handleEvent(SDL_Event e) {
	for (auto robot : robots) {
		if (robot != NULL) {
			robot->handleEvent(e);
		}
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
	updateMovements(robots, TOTAL_ROBOTS, timeStep);
	updateMovements(weapons, TOTAL_WEAPONS, timeStep);
	updateMovements(bullets, TOTAL_BULLETS, timeStep);

	//---COLLIDE ALL OBJECTS---
	updateAllCollisions(robots, TOTAL_ROBOTS, timeStep);
	updateAllCollisions(bullets, TOTAL_BULLETS, timeStep);
	
	//---SPAWN NEW OBJECTS---
	spawnBullets();
	
	//---Render All OBJECTS---
	updateRenders(robots, TOTAL_ROBOTS);
	updateRenders(weapons, TOTAL_WEAPONS);
	updateRenders(bullets, TOTAL_BULLETS);
	updateRenders(obstacles, TOTAL_OBSTACLES);

	//---UPDATE VISUALS---
	for (auto item : bars) {
		item->update();
		item->render();
	}

	//---DESPAWN DEAD OBJECTS---
	despawn(&robots, TOTAL_ROBOTS);
	despawn(&bullets, TOTAL_BULLETS);
	despawn(&weapons, TOTAL_WEAPONS);

	//--cout info--
	std::cout << "Size of bullets list = " << bullets.size() << std::endl;

}

// Explicitly generates Robots
void Game::genTestRobots() {
	NewRobot* robot0 = new NewRobot(500, 500, 0, gRenderer, &textures[0]);
	robot0->setHitbox();
	robot0->team = 1;
	robot0->setPlayer(0);
	robots.push_back(robot0);

	NewRobot* robot1 = new NewRobot(400, 300, 0, gRenderer, &textures[0]);
	robot1->setHitbox();
	robot1->team = 2;
	robot1->setPlayer(1);
	robots.push_back(robot1);
	
	StatusBar* health_bar1 = new StatusBar(25, 25, &robot1->health, gRenderer);
	bars.push_back(health_bar1);
	StatusBar* health_bar2 = new StatusBar(SCREEN_WIDTH - 25, 25, &robot0->health, gRenderer);
	health_bar2->reverse();
	bars.push_back(health_bar2);

}

// Explicitly generates Weapons
void  Game::genTestWeapon() {
	NewWeapon* weapon = new NewWeapon(10, 10, 0, gRenderer, &textures[1]);
	weapon->setHitbox();
	weapon->team = 1;
	weapon->setPlayer(0);
	weapon->setRelative(*robots.begin()); //relative pointer acting as origin (this is a dirty method)
	weapons.push_back(weapon);
	
	weapon = new NewWeapon(10, 10, 0, gRenderer, &textures[1]);
	weapon->setHitbox();
	weapon->team = 2;
	weapon->setPlayer(1);
	weapon->setRelative(*(++robots.begin())); //relative pointer acting as origin (this is a dirty method)
	weapons.push_back(weapon);

}

// Progressively generates bullets
void Game::genTestBullets(NewWeapon* weapon) {
	Bullet* new_bullet = new Bullet(weapon->getPosX(), weapon->getPosY(), weapon->getAngle(), 1200, gRenderer, &textures[2]);
	new_bullet->setHitbox();
	new_bullet->setTeam(weapon->team);
	bullets.push_back(new_bullet);
}

// Explicitly generates obstacles
void  Game::genTestObstacles() {
	GameObject* obstacle0 = new GameObject(300, 300, 0, gRenderer, &textures[3]);
	obstacle0->setHitbox();
	obstacles.push_back(obstacle0);

	GameObject* obstacle1 = new GameObject(600, 100, 0, gRenderer, &textures[3]);
	obstacle1->setHitbox();
	obstacles.push_back(obstacle1);
}


// Updates entire robot array by checking thigs they collide with
void Game::updateAllCollisions(std::list<NewRobot*> robotlist, int length, float timeStep) {
	for (auto robot : robotlist) {
		if (robot != NULL) {
			robot->updateBorderCollision(SCREEN_WIDTH, SCREEN_HEIGHT, timeStep);
			updateCollisions(robot, robots, TOTAL_ROBOTS, timeStep);
			updateCollisions(robot, obstacles, TOTAL_OBSTACLES, timeStep);
			updateCollisions(robot, bullets, TOTAL_BULLETS, timeStep);
		}
	}
}

// Updates entire bullet array by checking thigs they collide with
void Game::updateAllCollisions(std::list<Bullet*> mybullets, int length, float timeStep) {
	for (auto bullet : bullets) {
		if (bullet != NULL) {
			bullet->updateBorderCollision(SCREEN_WIDTH, SCREEN_HEIGHT);
			updateCollisions(bullet, robots, TOTAL_ROBOTS, timeStep);
			updateCollisions(bullet, obstacles, TOTAL_OBSTACLES, timeStep);
		}
	}
}

// Checks if a weapon is firing and spawns a bullet
void Game::spawnBullets() {
	for (auto weapon : weapons) {
		if (weapon != NULL && weapon->isFiring) {
			if (timeTracker.testGunFire()) {
				genTestBullets(weapon);
				soundEffects.playgLow();
			}
			
		}
	}
}

std::string Game::findWorkingDir() {
	char buf[256];
	GetCurrentDirectoryA(256, buf);
	return std::string(buf) + '\\';
}
