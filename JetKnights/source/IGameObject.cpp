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
	jks::Position position{ m_x, m_y, m_ang };
	if (parent != nullptr) {
		position += parent->getPositionAbsolute();
	}
	return position;
}

void IGameObject::render() {
	if (!isDead && isActive) {
		jks::Position pos_abs = getPositionAbsolute();
		
		renderOrigin(pos_abs.m_x, pos_abs.m_y);
		renderHitbox();

		// Render Children
		for (auto child : childs) {
			child->render();
			// Render blue connecting lines
			jks::Position child_pos_abs = child->getPositionAbsolute();
			SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
			SDL_RenderDrawLine(gRenderer, pos_abs.m_x, pos_abs.m_y, child_pos_abs.m_x, child_pos_abs.m_y);
		}
	}
}

// Render blue origin for object at absolute position (x,y)
void IGameObject::renderOrigin(float m_x, float m_y) {
	
	int offset = 4;

	int pixX = static_cast<int>(m_x - offset);
	int pixY = static_cast<int>(m_y - offset);
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

std::list<Hitbox>& IGameObject::getHitboxes() {
	return hitboxes;
}

bool IGameObject::isColliding(IGameObject* otherObj) {
	std::cout << this << " colliding with " << otherObj << std::endl;
	
	if (this == otherObj) {
		std::cout << "self collision detected, returning false" << std::endl;
		return false;
	}
	for (auto& hitbox : hitboxes) {
		for (auto& otherHitbox : otherObj->getHitboxes()) {
			return hitbox.chkCollision(otherHitbox);
		}
	}
}

std::list<IGameObject*> IGameObject::getAllObjects() {
	
	std::list<IGameObject*> allObjs;

	if (parent != nullptr) {
		allObjs = parent->getAllObjects();
	}
	else {
		allObjs = getAllChildren();
		allObjs.push_back(this); // add the current obj too
	}
	
	return allObjs;
}

std::list<IGameObject*> IGameObject::getAllChildren() {
	std::list<IGameObject*> allChilds;

	for (auto& child : childs) {
		allChilds.push_back(child);
		
		std::list<IGameObject*> grandchilds = child->getAllChildren();
		for (auto& grandchild : grandchilds) {
			allChilds.push_back(grandchild);
		}
	}

	return allChilds;
}

void IGameObject::addHitbox(Hitbox& hitbox) {
	hitbox.parentObj = this;
	hitboxes.push_back(hitbox);
}