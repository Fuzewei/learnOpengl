#pragma once
#include <vector>
#include <memory>
#include "Components/ComponentBase.h"
#include "types.h"
class Object
{
public:
	Object();
	~Object();
	void addComponent(std::shared_ptr<ComponentBase>component);
	template<typename T>
	std::shared_ptr<ComponentBase> getComponent();

private:
	UUID m_UUID;
	std::vector<std::shared_ptr<ComponentBase>> components;
};

template<typename T>
inline std::shared_ptr<ComponentBase> Object::getComponent()
{
	const type_info& type1 = typeid(T);
	T *result = nullptr;
	for (size_t i = 0; i < components.size(); i++)
	{
		std::shared_ptr<ComponentBase> item = components[i];
		const type_info& type2 = typeid(*item);
		if (type1 == type2)
			result = item;
	}
	return result;
}
