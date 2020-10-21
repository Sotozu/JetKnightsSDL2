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
#include "LTimer.h"
#include <SDL_mixer.h>


//Screen dimension constants
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;


//Starts up SDL and creates window
bool init();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Game Controller 1 and 2 handler
SDL_GameController* gGameController0 = NULL;
SDL_GameController* gGameController1 = NULL;

int main( int argc, char* args[] )
{
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
			Game game(gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);
			

			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					//Passes all events to game which parses and executes
					game.handleEvent(e);
				}
				//Calculate time step
				float timeStep = stepTimer.getTicks() / 1000.f;
				//std::cout << timeStep << std::endl;
				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//Updates all objects in the game for every loop
				/*Currently updates on each loop (process).
				Will change to update at a certain fps (60).*/
				game.updateObjects2(timeStep);

				//Restart step timer

				stepTimer.start();

				SDL_RenderPresent( gRenderer );
			}
		
	}

	/*
	WILL CREATE A FUNCTION THAT CLOSES AND 
	DELETES PROGRAMS THAT USE DYNAMIC MEMORY
	*/

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