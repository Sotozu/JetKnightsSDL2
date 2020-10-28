#pragma once
#include <SDL.h>
#include <iostream>
#include "GameObject.h"

class StatusBar{
public:
	// Constructors
	StatusBar();
	StatusBar(int x, int y, int* status, SDL_Renderer* renderer);
	
	// Modifiers
	void update();
	void render();

	// Accesors
	int getX();
	int getY();
	
private:
	static const int WIDTH = 300;
	static const int HEIGHT = 15;

	int x, y;
	int* status;
	int max_bar;
	int val;
	SDL_Renderer* renderer;
	SDL_Rect rect;	
};

