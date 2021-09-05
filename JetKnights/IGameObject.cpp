#include "IGameObject.h"

void IGameObject::addChild(IGameObject* child) {
	child->parent = this;
	childs.push_back(child);
}