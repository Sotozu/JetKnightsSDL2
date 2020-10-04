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



//#include "LTexture.h"

//Screen dimension constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

const int JOYSTICK_DEAD_ZONE = 8000;


//Starts up SDL and creates window
bool init();



//Frees media and shuts down SDL
//void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Game Controller 1 handler
SDL_GameController* gGameController = NULL;
SDL_Joystick* gJoyStick1 = NULL;
SDL_Joystick* gJoyStick2 = NULL;

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
	
			Game game(gRenderer);
			game.genTestWeapon();

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
					game.handleEvent(e);
				}

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//Testing Game object and its rendering
				game.genTestBullets();
				game.updateObjects();

				SDL_RenderPresent( gRenderer );
			}
		
	}

	//Free resources and close SDL
	//close();

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
			gGameController = SDL_GameControllerOpen(0);
			gJoyStick1 = SDL_JoystickOpen(0);
			gJoyStick1 = SDL_JoystickOpen(1);

			if (gGameController == NULL)
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