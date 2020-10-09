#include "Game.h"


Game::Game(SDL_Renderer* renderer) {
	gRenderer = renderer;
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
	images = { "assets/robotrightnew.png",
				"assets/cannonsmall.png",
				"assets/bullet-2.png",
				"assets/crate.png" };

	//Sets all robots at the beginning to not boosting
	for (int i = 0; i < TOTAL_ROBOTS; i++) {
		isRobotBoosting[i] = false;
	}

	loadMedia();

	genTestRobots();
	genTestObstacles();
	genTestWeapon();
}

void Game::loadMedia() {
	for (int i = 0; i < TOTAL_IMAGES; ++i) {
		textures[i].loadFromFile(images[i], gRenderer);
		//std::cout << "Texture loaded!!!" << std::endl;
	}
}

// Passes SDL events to classes that use them
void Game::handleEvent(SDL_Event e) {
	for (int i = 0; i < TOTAL_ROBOTS; ++i) {
		if (robots[i] != NULL) {

			robots[i]->handleEvent(e);

			////If the player presses the right trigger then this will come true
			//if (robots[i]->isPlayerBoosting(e) == true) {

			//	isRobotBoosting[i] = true;
			//}
			//else {
			//	isRobotBoosting[i] = false;
			//}
		}
	}
	for (int i = 0; i < TOTAL_WEAPONS; i++) {
		if (weapons[i] != NULL) {
			weapons[i]->handleEvent(e);
		}
	}

}

// Update order of the game
void Game::updateObjects2() {
	//---SPAWN NEW OBJECTS---
	spawnBullets();

	//---MOVE ALL OBJECTS---
	updateMovements(robots, TOTAL_ROBOTS);
	//updateMovements(weapons, TOTAL_WEAPONS);
	//updatePlayerBoost();
	for (int i = 0; i < TOTAL_WEAPONS; ++i) {
		if ( weapons[i] != NULL ){
			if (robots[i] == NULL) {
				weapons[i]->isDead = true;
			}
			else {
				weapons[i]->setPos(robots[i]->getPosX(), robots[i]->getPosY(), 0); // temporary untill weapon movement is properly implemented
				weapons[i]->update();
			}
		}
	}
	updateMovements(bullets, TOTAL_BULLETS);

	//---COLLIDE ALL OBJECTS---
	updateAllCollisions(robots, TOTAL_ROBOTS);
	//updateAllCollisions(weapons, TOTAL_WEAPONS);  // There is no weapon collision
	updateAllCollisions(bullets, TOTAL_BULLETS);
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
			std::cout << "Player" << i << " HP = " << robots[i]->getHealth() << std::endl;
		}
	}
}
	
//<<<<<<< HEAD
//
////Iterates through each weapon in Game and if it is firing then it will generate bullets
//void Game::updateBulletCreation() {
//
//	for (int i = 0; i < TOTAL_WEAPONS; i++) {
//		if (isWeaponFiring[i] == true) {
//			int n = 1;
//			int n_bullets = 1;
//			for (int i = 0; i < TOTAL_BULLETS; ++i) {
//				if (bullets[i] == NULL && n_bullets > 0) {
//					bullets[i] = new Bullet(weapons[0]->getPosX(), weapons[0]->getPosY(), weapons[0]->getAngle(), 10, gRenderer, &textures[2]);
//					bullets[i]->setHitbox();
//					bullets[i]->team = 1;
//					//std::cout << i << std::endl;
//					n_bullets--;
//				}
//			}
//		}
//	}
//	
//}

void Game::updatePlayerBoost() {
	for (int i = 0; i < TOTAL_ROBOTS; i++) {
		if (robots[i] != NULL) {
			if (isRobotBoosting[i] == true) {
				robots[i]->boostOn();
			}
			else {
				robots[i]->boostOff();
			}
		}
	}
}

// Explicitly generates Robots
void Game::genTestRobots() {
	robots[0] = new NewRobot(500, 500, 0, gRenderer, &textures[0]);
	robots[0]->setHitbox();
	robots[0]->team = 1;
	robots[0]->setPlayer(0);
	robots[1] = new NewRobot(800, 600, 0, gRenderer, &textures[0]);
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
			bullets[i] = new Bullet(weapons[team - 1]->getPosX(), weapons[team - 1]->getPosY(), weapons[team - 1]->getAngle(), 10, gRenderer, &textures[2]);
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
void Game::updateAllCollisions(NewRobot* array[], int length) {
	for (int i = 0; i < length; ++i) {
		if (array[i] != NULL) {
			array[i]->updateBorderCollision(SCREEN_WIDTH, SCREEN_HEIGHT);
			updateCollisions(array[i], robots, TOTAL_ROBOTS);
			updateCollisions(array[i], obstacles, TOTAL_OBSTACLES);
			updateCollisions(array[i], bullets, TOTAL_BULLETS);
		}
	}
}

// Updates entire bullet array by checking thigs they collide with
void Game::updateAllCollisions(Bullet* array[], int length) {
	for (int i = 0; i < length; ++i) {
		if (array[i] != NULL) {
			array[i]->updateBorderCollision(SCREEN_WIDTH, SCREEN_HEIGHT);
			updateCollisions(array[i], robots, TOTAL_ROBOTS);
			updateCollisions(array[i], obstacles, TOTAL_OBSTACLES);
		}
	}
}

// Checks if a weapon is firing and spawns a bullet
void Game::spawnBullets() {
	for (int i = 0; i < TOTAL_WEAPONS; i++) {
		if (weapons[i] != NULL && weapons[i]->isFiring) {
			genTestBullets(weapons[i]->team);
		}
	}
}
