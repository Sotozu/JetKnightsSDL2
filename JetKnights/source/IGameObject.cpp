#include "IGameObject.h"

extern SDL_Renderer* gRenderer;

void IGameObject::addChild(IGameObject* child) {
	child->parent = this;
	childs.push_back(child);
}

void IGameObject::handleEvent(SDL_Event e) {
	onEvent(e);
	
	for (auto child : childs) {
		child->handleEvent(e);
	}
}

void IGameObject::handleUpdate(float timestep) {
	onUpdate(timestep);

	for (auto child : childs) {
		child->handleUpdate(timestep);
	}
}

jks::Position IGameObject::getPositionAbsolute() {
	jks::Position position{ x,y,ang };
	if (parent != nullptr) {
		position += parent->getPositionAbsolute();
	}
	return position;
}

void IGameObject::render() {
	if (!isDead && isActive) {
		jks::Position pos_abs = getPositionAbsolute();
		
		renderOrigin(pos_abs.x, pos_abs.y);
		renderHitbox();

		// Render Children
		for (auto child : childs) {
			child->render();
			// Render blue connecting lines
			jks::Position child_pos_abs = child->getPositionAbsolute();
			SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
			SDL_RenderDrawLine(gRenderer, pos_abs.x, pos_abs.y, child_pos_abs.x, child_pos_abs.y);
		}
	}
}

// Render blue origin for object at absolute position (x,y)
void IGameObject::renderOrigin(float x, float y) {
	
	int offset = 4;

	int pixX = static_cast<int>(x - offset);
	int pixY = static_cast<int>(y - offset);
	int pixW = offset * 2;
	int pixH = offset * 2;

	SDL_Rect origin = { pixX, pixY, pixW, pixH };

	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF); // Set color blue
	SDL_RenderFillRect(gRenderer, &origin);
}

jks::Type IGameObject::getType() {
	return jks::Type::NONE;
}

Hitbox& IGameObject::getHitbox() {
	for (auto& hitbox : hitboxes) {
		return hitbox;
	}
}

