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
		// Render blue Origin
		SDL_Rect origin = { pos_abs.x - 2, pos_abs.y - 2, 5, 5 };
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
		SDL_RenderFillRect(gRenderer, &origin);

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

jks::Type IGameObject::getType() {
	return jks::Type::NONE;
}

