/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include "LTexture.h"
#include "Game.h"
#include "Main_Menu.h"
#include "Pause_Menu.h"
#include "LTimer.h"
#include <SDL_mixer.h>
#include "ThemeMusic.h"
#include "Sound.h"


//Screen dimension constants
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;


//Starts up SDL and creates window
bool init();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//


//The window renderer
SDL_Renderer* gRenderer = NULL;

//Game Controller 1 and 2 handler
SDL_GameController* gGameController0 = NULL;
SDL_GameController* gGameController1 = NULL;


enum gameState {
	MAIN_MENU, PLAYING, PAUSE_MENU
};
int main( int argc, char* args[] )
{

	gameState state = MAIN_MENU;

	float timeStep, timeStepTwo;
	bool fightMusic = true, menuMusic = true, pauseMusic = true;

	bool gamePaused = false;

	bool wasInMenu = true;

	bool isPlaying = true;
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			LTimer stepTimer;
	
			//Initialize Game object with gRenderer


			std::unique_ptr<Game> game(new Game());

			//game->initialize(gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);

			game->initialize(gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);

			Pause_Menu pausemenu(gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);

			Main_Menu mainmenu(gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);
			


			
			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{

					switch (state) {
					case (MAIN_MENU):

						if (menuMusic == true) {
							game->stopMusic();
							game->playMenuTheme();
							menuMusic = false;
							fightMusic = true;
							pauseMusic = true;
						}

						if (e.type == SDL_QUIT)
						{
							quit = true;
						}
						else if (e.type == SDL_CONTROLLERBUTTONDOWN) {

							if (e.cbutton.which == 0) {
								if (e.cbutton.button == SDL_CONTROLLER_BUTTON_BACK) {
									std::cout << "IN MENUES" << std::endl;
									state = PLAYING;
								}
							}
						}
						break;

					case (PLAYING):
					
						if (fightMusic == true) {

							game->stopMusic();
							game->playFightTheme();
							menuMusic = true;
							fightMusic = false;
							pauseMusic = true;
						}
						if (e.type == SDL_QUIT)
						{
							quit = true;
						}
						else if (e.type == SDL_CONTROLLERBUTTONDOWN) {
							
							if (e.cbutton.which == 0) {
								if (e.cbutton.button == SDL_CONTROLLER_BUTTON_BACK) {
									std::cout << "NOW PLAYING" << std::endl;
									state = MAIN_MENU;
								}
								else if (e.cbutton.button == SDL_CONTROLLER_BUTTON_START) {
									std::cout << "PAUSE MENU" << std::endl;
									state = PAUSE_MENU;

									timeStepTwo = stepTimer.getTicks() / 1000.f;
									gamePaused = true;
								}




							}
						}
						game->handleEvent(e);
						break;

					case (PAUSE_MENU):

						game->handleEvent(e);


						if (pauseMusic == true) {
							game->stopMusic();
							game->playPauseTheme();
							menuMusic = true;
							fightMusic = true;
							pauseMusic = false;
						}

						if (e.type == SDL_QUIT)
						{
							quit = true;
						}

						else if (e.type == SDL_CONTROLLERBUTTONDOWN) {

							if (e.cbutton.button == SDL_CONTROLLER_BUTTON_START){
								std::cout << "NOW PLAYING" << std::endl;
								state = PLAYING;
							}
						}
						break;
					}

					//User requests quit
					
					//Passes all events to game which parses and executes
				}
				//Calculate time step
				if (state == PLAYING) {
					if (gamePaused == true){
						timeStep = timeStepTwo;
						gamePaused = false;
					}
					else {
						timeStep = stepTimer.getTicks() / 1000.f;
					}

					std::cout << stepTimer.getTicks() / 1000.f << std::endl;

					//Clear screen
					SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
					SDL_RenderClear(gRenderer);

					//Updates all objects in the game for every loop
					/*Currently updates on each loop (process).
					Will change to update at a certain fps (60).*/

					game->updateObjects(timeStep);

					//Restart step timer
					stepTimer.start();

					SDL_RenderPresent(gRenderer);
				}
				else if (state == MAIN_MENU) {

					timeStep = stepTimer.getTicks() / 1000.f;
					//Clear screen
					SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
					SDL_RenderClear(gRenderer);

					mainmenu.updateObjects(timeStep);

					SDL_RenderPresent(gRenderer);
					

				}
				else if (state == PAUSE_MENU) {
					timeStep = stepTimer.getTicks() / 1000.f;
					pausemenu.renderTransparentRect();
				}
			}
		
	}

	return 0;
}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Check for joysticks
		if (SDL_NumJoysticks() < 1)
		{
			printf("Warning: No joysticks connected!\n");
		}
		else
		{
			//Load joystick
			gGameController0 = SDL_GameControllerOpen(0);
			gGameController1 = SDL_GameControllerOpen(1);


			if (gGameController0 == NULL || gGameController1 == NULL)
			{
				printf("Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError());
			}
		}

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
		//Initialize SDL Mixer
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
			success = false;
		}
	}

	return success;
}
	
/*
NEED TO EXPAND ON THIS CLOSE FUNCTION
*/

//void close()
//{
//	//Free loaded images
//	gRobotTexture.free();
//	gWeapon1.free();
//
//
//	//Close game controller
//	SDL_GameControllerClose(gGameController);
//	gGameController = NULL;
//
//	//Destroy window	
//	SDL_DestroyRenderer(gRenderer);
//	SDL_DestroyWindow(gWindow);
//	gWindow = NULL;
//	gRenderer = NULL;
//
//	//Quit SDL subsystems
//	IMG_Quit();
//	SDL_Quit();
//}

/*
OTHER NOTES:
1. Do we pass the assets (textures etc) into the Game object OR do we load these assets within Game object.
	1a. Storing the textures into discriptively respective objects would make the program more atomic. but
	would cost us memory.
	1b. Given the size of the game memory usage is not a concern so the method in step 1a. is very viable.

	- Current opinion on 1. is that we will move forward to make it more atomic and place textures into
	respecitve object.


2. Weapon will be initialized withing the Robot class. This way position information is correclty shared.

*/