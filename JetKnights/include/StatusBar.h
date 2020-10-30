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

	void reverse();
	
private:
	static const int WIDTH = 300;
	static const int HEIGHT = 10;

	int x, y;
	int* status;
	int max_bar;
	int val;
	SDL_Renderer* renderer;
	SDL_Rect status_rect;
	SDL_Rect casing_rect;

	int direction = 1;
	bool show_casing = true;
};

