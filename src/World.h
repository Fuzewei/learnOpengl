#pragma once
#include <vector>
#include <memory>
#include "Object.h"
#include "Foundation/Singleton.h"

class World : public Singleton<World>
{
public:
	World();
	~World();
	void addObject( std::shared_ptr<Object> object);
	void Tick();
	
private:
	std::vector<std::shared_ptr<Object>> m_Objects;
};

