#pragma once

//�������
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

