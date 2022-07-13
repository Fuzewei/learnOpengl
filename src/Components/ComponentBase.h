#pragma once

//组件基类
class ComponentBase
{
public:

	ComponentBase() {}
	~ComponentBase() {}
	virtual void Awake() {}
	virtual void Update() {}
	virtual void UpdateRenderer() {}
private:
};

