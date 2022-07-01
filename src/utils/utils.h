#ifndef _utils
#define _utils
#include <Gl/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) glClearError();\
    x;\
    ASSERT(glCheckError());
enum ShaderType
{
    NONE = -1,
    VERTEX = 0,
    FRAGMENT = 1
};

struct ShaderProgram
{
    std::string vertexShader;
    std::string fragmantShader;
};

extern ShaderProgram praseShader(const std::string& filePath);

extern unsigned int compireShader(int type, const std::string& source);

extern unsigned int createShader(const std::string& vertexShader, const std::string& fragementShader);

extern void glClearError();

extern bool glCheckError();

#endif // !utils
