#include "World.h"

World::World()
{
}

World::~World()
{
}

void World::addObject(std::shared_ptr<Object> object)
{
	m_Objects.push_back(object);
}

void World::Tick()
{
	for (auto& object : m_Objects)//tickLogic
	{
		object->update();
	}
	for (auto& object : m_Objects)//tickRender
	{
		object->updateRender();
	}
}
