#pragma once

#include "IGameObject.h"

#include <SDL.h>

class Arena : public IGameObject {
public:
	Arena();
	void onEvent(SDL_Event e) override;
	void onUpdate(float timestep) override;
	jks::Type getType() override;
private:
	int width;
	int height;
};

