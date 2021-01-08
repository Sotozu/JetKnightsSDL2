
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


//The window renderer
SDL_Renderer* gRenderer = NULL;

//Game Controller 1 and 2 handler
SDL_GameController* gGameController0 = NULL;
SDL_GameController* gGameController1 = NULL;


/*
Depending on which state the game is in the program will execute specific code.
Instead of using arbitrary numbers to write program logic for specific game states we use an enumeration.
*/
enum class gameState {
	MAIN_MENU, PLAYING, PAUSE_MENU
};


int main( int argc, char* args[] )
{

	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Set the game state to main menu so the program starts at main menu
		gameState state = gameState::MAIN_MENU;

		//time value tracked by the game to make all time sensitive events work
		float timeStep, pausedTimeStamp;

		//tracks if the game has been paused
		bool wasGamePaused = false;

		//flag for when the user quits
		bool quit = false;

		//SDL Event Structure
		SDL_Event e;

		//Lazyfoo style timer class that has has info on timer
		LTimer stepTimer;
	
		//Dynamically created game so that we can delete it if we wish to start a new game 
		std::unique_ptr<Game> game(new Game());
		
		//This game function acts as a constructor for the game objects
		game->initialize(gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT, gGameController0, gGameController1);

		//Initialize the pause menu (will also make it dynamic later)
		Pause_Menu pausemenu(gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);

		//initialze the game menu (will also make it dynamic later)
		Main_Menu mainmenu(gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);
			

		
		//the "init" function creates the events of adding devices and some window events take place.
		//We need to get rid of these events before jumping into the main game loop that calls events
		SDL_PumpEvents();
		SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);

		//start the main menu theme music because the "state" is set to MAIN_MENU
		game->playMenuTheme();

		//Main game loop
		while( !quit )
		{
			
			//The event system in SDL is treating the controller events just like joystick events. So we get two events per input. 
			//We don't want to register these because it will result in excessive calls to the event loop.
			SDL_PumpEvents();
			SDL_FlushEvents(SDL_JOYAXISMOTION, SDL_JOYDEVICEREMOVED);

			//Event loop. Depending on the event type different actions will occur that affect the game
			while (SDL_PollEvent(&e) != 0)
			{
				//If the player quits the program by clicking the exit button on the window
				if (e.type == SDL_QUIT)
				{
					quit = true;
					break;
				}

				//If the player inputs the controller back button or controller start button.
				//This is to navigate between the main menu, pause menu and playing the game
				if (e.type == SDL_CONTROLLERBUTTONDOWN) {
					if (e.cbutton.which == 0 || e.cbutton.which == 1) {

						if (state == gameState::MAIN_MENU && e.cbutton.button == SDL_CONTROLLER_BUTTON_BACK) {
							state = gameState::PLAYING;
							game->stopMusic();
							game->playFightTheme();

						}
						else if (state == gameState::PLAYING && e.cbutton.button == SDL_CONTROLLER_BUTTON_BACK) {
							state = gameState::PAUSE_MENU;
							wasGamePaused = true;
							pausedTimeStamp = stepTimer.getTicks() / 1000.f;
							pausemenu.stopMusic();
							pausemenu.playPauseTheme();

						}
						else if (state == gameState::PLAYING && e.cbutton.button == SDL_CONTROLLER_BUTTON_START) {
							state = gameState::MAIN_MENU;
							game->stopMusic();
							game->playMenuTheme();
						}
						else if (state == gameState::PAUSE_MENU && e.cbutton.button == SDL_CONTROLLER_BUTTON_BACK) {
							state = gameState::PLAYING;
							game->unpauseGame();

							game->stopMusic();
							game->playFightTheme();
						}
					}
				}


				//Depending on which state we are in the game then only one of these switch cases will activate
				switch (state) {

				case (gameState::MAIN_MENU):
					//there is currently nothing done here (will need to develop the main menu section of the game
					break;

				case (gameState::PLAYING):

					game->handleEvent(e);

					break;

				case (gameState::PAUSE_MENU):
					game->pauseGame(e);
					break;
				}

			}

			/*NOW WE HAVE HANDLED ALL EVENTS AND IT IS TIME TO UPDATE THE OBJECTS IN THE PROGRAM*/

			if (state == gameState::PLAYING) {
				//Creates a time stamp so that when the game unpauses the game timer "resets" to that positions 

				if (wasGamePaused == true){

					//sets the timeStep to the time value of when the game was paused
					timeStep = pausedTimeStamp; 
					wasGamePaused = false;
				}
				else {
					//set timeStep
					timeStep = stepTimer.getTicks() / 1000.f;
				}

				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				//For each event this updates all objects in the game.
				game->updateObjects(timeStep);

				//Restart step timer
				stepTimer.start();

				//renders all updated objects
				SDL_RenderPresent(gRenderer);
			}
			else if (state == gameState::MAIN_MENU) {

				//set timeStep
				timeStep = stepTimer.getTicks() / 1000.f;

				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				//updates all main menu objects
				mainmenu.updateObjects(timeStep);

				SDL_RenderPresent(gRenderer);
					

			}
			else if (state == gameState::PAUSE_MENU) {
				//set timeStep
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
