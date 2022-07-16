#pragma once

//组件基类
class ComponentBase
{
public:

	ComponentBase() {}
	virtual ~ComponentBase() {}
	virtual void Awake() {}
	virtual void Update() {}
	virtual void UpdateRender() {}
private:
};

