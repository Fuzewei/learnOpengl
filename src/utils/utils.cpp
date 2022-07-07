#include <src/utils/utils.h>

 void glClearError()
 {
     while (glGetError() != GL_NO_ERROR);
 }

 bool glCheckError()
 {
     while (auto error = glGetError())
     {
         std::cout << "[opengl error]" << error << std::endl;
         return false;
     }
     return true;
 }