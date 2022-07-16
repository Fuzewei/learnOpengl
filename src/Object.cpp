#include "Object.h"

Object::Object()
{
}

Object::~Object()
{
}

void Object::update()
{
	for (auto& component : components)
	{
		component->Update();
	}
}

void Object::updateRender()
{
	for (auto& component : components)
	{
		component->UpdateRender();
	}
}

void Object::addComponent(std::shared_ptr<ComponentBase> component)
{
	components.push_back(component);
}


