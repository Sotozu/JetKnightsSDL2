#pragma once
#include "IGameObject.h"
class Obstacle : public IGameObject {
public:
	Obstacle();
	Obstacle(float m_x, float m_y, float ang);

	void onEvent(SDL_Event e) override;
	void onUpdate(float timestep) override;

	void renderHitbox() override;

	void addDefaultHitbox();

	jks::Type getType() override;
};

