#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class Hitbox : public SDL_Rect {
public:
	// Constructors
	Hitbox();
	Hitbox(int posX, int posY, int width, int height, SDL_Renderer* renderer);

	// Mutators
	void setPos(int PosX, int posY);
	void setPosX(int posX);
	void setPosY(int posY);
	void setParameters(int x, int y, int width, int height, SDL_Renderer* renderer);

	// Accessors
	bool chkCollision(Hitbox* b);
	bool chkBorderCollisionX(int);
	bool chkBorderCollisionY(int);
	int getWidth();
	int getHeight();
	SDL_Rect* getRect();
	int getPosX();
	int getPosY();

	void render();

	//Data
	float relX, relY; //relative position of hitbox to GameObject

private:
	SDL_Renderer* gRenderer;
};
