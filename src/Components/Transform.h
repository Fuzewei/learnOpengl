#pragma once
#include "ComponentBase.h"
#include "glm/glm.hpp"
class Transform : public ComponentBase
{
public:
	
	Transform();
	~Transform();

private:
	glm::mat4x4 m_Viex;
	glm::mat4x4 m_Proj;
	glm::mat4x4 m_Modle;
	glm::vec3 m_Position;
	glm::vec3 m_Rotation;
	glm::vec3 m_Scale;

};

