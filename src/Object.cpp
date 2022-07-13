#include "Object.h"

Object::Object()
{
}

Object::~Object()
{
}

void Object::addComponent(std::shared_ptr<ComponentBase> component)
{
	components.push_back(component);
}


