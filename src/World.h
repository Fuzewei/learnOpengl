#pragma once
#include <vector>
#include <memory>
#include "Object.h"
#include "Foundation/Singleton.h"

class World : public Singleton<World>
{
public:
	void addObject( std::shared_ptr<Object> object);
	
private:
	std::vector<std::shared_ptr<Object>> m_Objects;
};

