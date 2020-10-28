#include "Game.h"


//Constructor
Game::Game(SDL_Renderer* renderer, int screenW, int screenH) {
	SCREEN_HEIGHT = screenH;
	SCREEN_WIDTH = screenW;
	gRenderer = renderer;
	//Sets array to null (empty)
	for (int i = 0; i < TOTAL_ROBOTS; i++) {
		robots[i] = NULL;
	}
	for (int i = 0; i < TOTAL_WEAPONS; i++) {
		weapons[i] = NULL;
	}
	for (int i = 0; i < TOTAL_BULLETS; i++) {
		bullets[i] = NULL;
	}
	for (int i = 0; i < TOTAL_OBSTACLES; i++) {
		obstacles[i] = NULL;
	}
	//List of assets that we will be using in the game
	images = { "C:/source/JetKnights/JetKnights/assets/images/robotrightnew.png",
				"C:/source/JetKnights/JetKnights/assets/images/cannonsmall.png",
				"C:/source/JetKnights/JetKnights/assets/images/bullet-2.png",
				"C:/source/JetKnights/JetKnights/assets/images/crate.png" };

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
	for (int i = 0; i < TOTAL_ROBOTS; ++i) {
		if (robots[i] != NULL) {
			robots[i]->handleEvent(e);
		}
	}
	for (int i = 0; i < TOTAL_WEAPONS; i++) {
		if (weapons[i] != NULL) {
			weapons[i]->handleEvent(e);
		}
	}

}

// Update order of the game
void Game::updateObjects2(float timeStep) {
	//---SPAWN NEW OBJECTS---
	spawnBullets();

	//---MOVE ALL OBJECTS---
	updateMovements(robots, TOTAL_ROBOTS, timeStep);

	for (int i = 0; i < TOTAL_WEAPONS; ++i) {
		if ( weapons[i] != NULL ){
			if (robots[i] == NULL) {
				weapons[i]->isDead = true;
			}
			else {
				weapons[i]->setPos(robots[i]->getPosX(), robots[i]->getPosY(), 0);
				weapons[i]->update();
			}
		}
	}

	updateMovements(bullets, TOTAL_BULLETS, timeStep);

	//---COLLIDE ALL OBJECTS---
	updateAllCollisions(robots, TOTAL_ROBOTS, timeStep);
	//updateAllCollisions(weapons, TOTAL_WEAPONS);  // There is no weapon collision
	updateAllCollisions(bullets, TOTAL_BULLETS, timeStep);
	updateRenders(robots, TOTAL_ROBOTS);
	updateRenders(weapons, TOTAL_WEAPONS);
	updateRenders(bullets, TOTAL_BULLETS);
	updateRenders(obstacles, TOTAL_OBSTACLES);

	//---DESPAWN DEAD OBJECTS---
	despawn(robots, TOTAL_ROBOTS);
	despawn(bullets, TOTAL_BULLETS);
	despawn(weapons, TOTAL_WEAPONS);

	//---COUT INFO---
	for (int i = 0; i < TOTAL_ROBOTS; i++) {
		if (robots[i] != NULL) {
		}
	}
}

// Explicitly generates Robots
void Game::genTestRobots() {
	robots[0] = new NewRobot(500, 500, 0, gRenderer, &textures[0]);
	robots[0]->setHitbox();
	robots[0]->team = 1;
	robots[0]->setPlayer(0);
	robots[1] = new NewRobot(400, 300, 0, gRenderer, &textures[0]);
	robots[1]->setHitbox();
	robots[1]->team = 2;
	robots[1]->setPlayer(1);
}

// Explicitly generates Weapons
void  Game::genTestWeapon() {
	weapons[0] = new NewWeapon(10, 10, 0, gRenderer, &textures[1]);
	weapons[0]->setHitbox();
	weapons[0]->team = 1;
	weapons[0]->setPlayer(0);
	weapons[1] = new NewWeapon(10, 10, 0, gRenderer, &textures[1]);
	weapons[1]->setHitbox();
	weapons[1]->team = 2;
	weapons[1]->setPlayer(1);

}

// Progressively generates bullets
void Game::genTestBullets(int team) {
	for (int i = 0; i < TOTAL_BULLETS; ++i) {
		if (bullets[i] == NULL) {
			bullets[i] = new Bullet(weapons[team - 1]->getPosX(), weapons[team - 1]->getPosY(), weapons[team - 1]->getAngle(), 1200, gRenderer, &textures[2]);
			bullets[i]->setHitbox();
			bullets[i]->setTeam(team);
			return;
		}
	}
}

// Explicitly generates obstacles
void  Game::genTestObstacles() {
	obstacles[0] = new GameObject(300, 300, 0, gRenderer, &textures[3]);
	obstacles[0]->setHitbox();
	obstacles[1] = new GameObject(600, 100, 0, gRenderer, &textures[3]);
	obstacles[1]->setHitbox();
}


// Updates entire robot array by checking thigs they collide with
void Game::updateAllCollisions(NewRobot* array[], int length, float timeStep) {
	for (int i = 0; i < length; ++i) {
		if (array[i] != NULL) {
			array[i]->updateBorderCollision(SCREEN_WIDTH, SCREEN_HEIGHT, timeStep);
			updateCollisions(array[i], robots, TOTAL_ROBOTS, timeStep);
			updateCollisions(array[i], obstacles, TOTAL_OBSTACLES, timeStep);
			updateCollisions(array[i], bullets, TOTAL_BULLETS, timeStep);
		}
	}
}

// Updates entire bullet array by checking thigs they collide with
void Game::updateAllCollisions(Bullet* array[], int length, float timeStep) {
	for (int i = 0; i < length; ++i) {
		if (array[i] != NULL) {
			array[i]->updateBorderCollision(SCREEN_WIDTH, SCREEN_HEIGHT);
			updateCollisions(array[i], robots, TOTAL_ROBOTS, timeStep);
			updateCollisions(array[i], obstacles, TOTAL_OBSTACLES, timeStep);
		}
	}
}

// Checks if a weapon is firing and spawns a bullet
void Game::spawnBullets() {
	for (int i = 0; i < TOTAL_WEAPONS; i++) {
		if (weapons[i] != NULL && weapons[i]->isFiring) {
			//std::cout << SDL_GetTicks() << std::endl; 
			if (timeTracker.testGunFire()) {
				genTestBullets(weapons[i]->team);
				soundEffects.playgLow();
			}
			
		}
	}
}
