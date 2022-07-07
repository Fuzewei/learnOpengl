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

extern void glClearError();

extern bool glCheckError();

#endif // !utils
