#include <src/utils/utils.h>

 ShaderProgram praseShader(const std::string& filePath)
{
    std::ifstream file(filePath);
    std::string line;
    ShaderType shaderType = ShaderType::NONE;
    std::stringstream ss[2];
    while (std::getline(file, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                shaderType = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                shaderType = ShaderType::FRAGMENT;
            }
        }
        else
        {
            ss[shaderType] << line << std::endl;
        }
    }
    return { ss[ShaderType::VERTEX].str(), ss[ShaderType::FRAGMENT].str() };
}

 unsigned int compireShader(int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Falied co compile:" << (type == GL_VERTEX_SHADER ? " vertex shader" : "fragement shader")
            << std::endl;
        std::cout << message << std::endl;
    }
    return id;
}


 unsigned int createShader(const std::string& vertexShader, const std::string& fragementShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = compireShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compireShader(GL_FRAGMENT_SHADER, fragementShader);
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);
    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
}

 void glClearError()
 {
     while (glGetError() != GL_NO_ERROR);
 }

 bool glCheckError()
 {
     while (auto error =glGetError() )
     {
         std::cout << "[opengl error]" << error << std::endl;
         return false;
     }
     return true;
 }