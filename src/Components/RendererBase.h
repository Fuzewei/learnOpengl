#pragma once
#include "ComponentBase.h"
class RendererBase : public ComponentBase
{

public:
	RendererBase();
	~RendererBase();
	void Render();
private:
};

