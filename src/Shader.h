#pragma once
#include <string>
#include <map>
#include "types.h"

struct ShaderProgram
{
	std::string vertexShader;
	std::string fragmantShader;
};

enum ShaderType
{
	NONE = -1,
	VERTEX = 0,
	FRAGMENT = 1
};


class Shader {
public:
	Shader(std::string filePath);
	~Shader();
	void bind() const;
	void unBind() const;
	void setUniform4f(const std::string &name, float v0, float v1, float v2, float v3);
	void setUniform1i(const std::string& name, int v0);
private:
	mutable std::map<std::string, int> uniformLocationBuffer;
	std::string m_FilePath;
	RenderId m_RenderID;
	int getUnformNameLocation(const std::string &name) const;

	ShaderProgram praseShader();
	RenderId compireShader(unsigned int type, const std::string& source);
	RenderId createProgram(const std::string& vertexShader, const std::string& fragementShader);
};