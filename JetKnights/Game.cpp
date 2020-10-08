#include "Game.h"


Game::Game(SDL_Renderer* renderer) {
	//const int totalImages = 3;
	//const int totalBullets = 3;
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

	//Sets all weapons at the beginning to a not firing state
	for (int i = 0; i < TOTAL_WEAPONS; i++) {
		isWeaponFiring[i] = false;
	}

	loadMedia();

	genTestRobots();
	genTestObstacles();
	genTestWeapon();
}

void Game::handleEvent(SDL_Event e) {

	for (int i = 0; i < TOTAL_ROBOTS; ++i) {
		if (robots[i] != NULL) {
			robots[i]->handleEvent(e);
		}
	}
	for (int i = 0; i < TOTAL_WEAPONS; i++) {
		if (weapons[i] != NULL) {
			//updates movement of the weapon
			weapons[i]->handleEvent(e);
			//updates if the weapon is firing
			if (weapons[i]->WeaponFiring(e) == true) {
				//std::cout << "WORKS!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;

				isWeaponFiring[i] = true;
			}
			else {
				//std::cout << "IS NOT FIRING" << std::endl;

				isWeaponFiring[i] = false;
			}
		}
	}

	//Creates Bullets

}
/*
The update should be set in the following order because object are dependent on other objects updates
1.Robot
2.Weapon
3.Bullet
*/
void Game::updateObjects() {
	//std::cout << "updating objects " << std::endl;
	
	updateRobots();
	updateWeapons();
	for (int i = 0; i < TOTAL_WEAPONS; i++) {
		if (isWeaponFiring[i] == true) {
			//std::cout << "IS FIRING BITCHHHHHHHHHHHHHHHHHHHHHHHHHHHH" << std::endl;
			genTestBullets();
		}
	}
	
	updateBullets();
	updateObstacles();
	

}

void Game::updateObjects2() {
	//---SPAWN NEW OBJECTS---
	//spawn()
	for (int i = 0; i < TOTAL_WEAPONS; i++) {
		if (isWeaponFiring[i] == true) {
			//std::cout << "IS FIRING BITCHHHHHHHHHHHHHHHHHHHHHHHHHHHH" << std::endl;
			genTestBullets();
		}
	}

	//---MOVE ALL OBJECTS---
	updateMovements(robots, TOTAL_ROBOTS);
	//updateMovements(weapons, TOTAL_WEAPONS);
	weapons[0]->setPos(robots[0]->getPosX(), robots[0]->getPosY(), 0); // temporary untill weapon movement is properly implemented
	weapons[0]->update();
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

	//---COUT tests---
	if (robots[1] != NULL) {
		std::cout << robots[1]->getHealth() << std::endl;
	}
	//std::cout << "game tick completed" << std::endl;
	
}

void Game::updateRobots() {
	for (int i = 0; i < TOTAL_ROBOTS; ++i) {
		if (robots[i] != NULL) {
			robots[i]->update();
			if(robots[i]->updateBorderCollision(SCREEN_WIDTH, SCREEN_HEIGHT)){}
			else {
				updateCollisions(robots[i], obstacles, TOTAL_OBSTACLES);
				updateCollisions(robots[i], robots, TOTAL_ROBOTS);
				updateCollisions(robots[i], bullets, TOTAL_BULLETS);
			}	
			robots[i]->render();
		}
	}
}

void Game::updateWeapons() {
	for (int i = 0; i < TOTAL_WEAPONS; ++i) {
		if (weapons[i] != NULL) {
			weapons[i]->setPos(robots[0]->getPosX(), robots[0]->getPosY(), 0);
			weapons[i]->update();
			weapons[i]->render();
		}
	}
}

void Game::updateBullets() {
	for (int i = 0; i < TOTAL_BULLETS; ++i) {
		if (bullets[i] != NULL) {
			bullets[i]->update();
			if (bullets[i]->chkBorderCollision(SCREEN_WIDTH, SCREEN_HEIGHT) ||
				chkCollisions(robots, TOTAL_ROBOTS, bullets[i]) || 
				chkCollisions(obstacles, TOTAL_OBSTACLES, bullets[i]))
			{
				bullets[i]->isDead = true;
			}
			bullets[i]->render();
		}
	}
	for (int i = 0; i < TOTAL_BULLETS; ++i) {
		if (bullets[i] != NULL && bullets[i]->isDead) {
			delete bullets[i];
			bullets[i] = NULL;
		}
	}
}

void Game::updateObstacles() {
	for (int i = 0; i < TOTAL_OBSTACLES; ++i) {
		if (obstacles[i] != NULL) {
			obstacles[i]->render();
		}
	}
}
	
void Game::genTestBullets() {
	for (int i = 0; i < TOTAL_BULLETS; ++i) {
		if (bullets[i] == NULL) {
			bullets[i] = new Bullet(weapons[0]->getPosX(), weapons[0]->getPosY(), weapons[0]->getAngle() , 10, gRenderer, &textures[2]);
			bullets[i]->setHitbox();
			bullets[i]->team = 1;
			return;
		}
	}
}
void Game::genTestRobots() {
	robots[0] = new NewRobot(500, 500, 0, gRenderer, &textures[0]);
	robots[0]->setHitbox();
	robots[0]->team = 1;
	robots[1] = new NewRobot(800, 600, 0, gRenderer, &textures[0]);
	robots[1]->setHitbox();
	robots[1]->team = 0;
	robots[1]->setPlayer(1);
}

void Game::loadMedia() {
	for (int i = 0; i < TOTAL_IMAGES; ++i) {
		textures[i].loadFromFile(images[i], gRenderer);
		//std::cout << "Texture loaded!!!" << std::endl;
	}
}


void  Game::genTestWeapon() {
	weapons[0] = new NewWeapon(10, 10, 0, gRenderer, &textures[1]);
	weapons[0]->setHitbox();
	weapons[0]->team = 1;
}

void  Game::genTestObstacles() {
	obstacles[0] = new GameObject(300, 300, 0, gRenderer, &textures[3]);
	obstacles[0]->setHitbox();
	obstacles[1] = new GameObject(600, 100, 0, gRenderer, &textures[3]);
	obstacles[1]->setHitbox();
}

void Game::WeaponFiring(SDL_Event e) {

	//Handle BUllet Creation
	if (e.type == SDL_CONTROLLERAXISMOTION) {
		//Joystick input

		//If player 1 input
		if (e.caxis.which == 0) {
			if (e.caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERRIGHT) {
				genTestBullets();
				//std::cout << "BLAH" << std::endl;

			}
		}
	}
}

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


void Game::updateAllCollisions(Bullet* array[], int length) {
	for (int i = 0; i < length; ++i) {
		if (array[i] != NULL) {
			array[i]->updateBorderCollision(SCREEN_WIDTH, SCREEN_HEIGHT);
			updateCollisions(array[i], robots, TOTAL_ROBOTS);
			updateCollisions(array[i], obstacles, TOTAL_OBSTACLES);
		}
	}
}

