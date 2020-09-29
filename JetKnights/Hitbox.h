#pragma once
#include <SDL.h>
#include <SDL_image.h>

class Hitbox : public SDL_Rect {
public:
	Hitbox(int posX, int posY, int width, int height, SDL_Renderer* renderer);
	bool chkCollision(Hitbox b);
	int getWidth();
	int getHeight();
	SDL_Rect* getRect();
private:
	SDL_Renderer* gRenderer;
};
