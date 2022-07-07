#include "Shader.h"
#include <src/utils/utils.h>

Shader::Shader(std::string filePath):
	m_FilePath(filePath)
{
    ShaderProgram soure = praseShader();
    m_RenderID = createProgram(soure.vertexShader, soure.fragmantShader);
    bind();
}

Shader::~Shader()
{
}

void Shader::bind()const
{
    GLCall(glUseProgram(m_RenderID));
}

void Shader::unBind()const
{
    GLCall(glUseProgram(0));
}

void Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    GLCall(glUniform4f(getUnformNameLocation(name), v0, v1, v2, v3));
}

void Shader::setUniform1i(const std::string& name, int v0)
{
    GLCall(glUniform1i(getUnformNameLocation(name), v0));
}

int Shader::getUnformNameLocation(const std::string& name) const
{
    if (uniformLocationBuffer.find(name) != uniformLocationBuffer.end())
    {
        return uniformLocationBuffer[name];
    }
    GLCall(int location = glGetUniformLocation(m_RenderID, name.c_str()));
    if (location == -1)
    {
        std::cout << "get uniform err name :"<< name << std::endl;
    }
    uniformLocationBuffer[name] = location;
    return location;
}


ShaderProgram Shader::praseShader()
{
    std::ifstream file(m_FilePath);
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

RenderId Shader::compireShader(unsigned int type, const std::string& source)
{
    RenderId id = glCreateShader(type);
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, NULL));
    GLCall(glCompileShader(id));
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

RenderId Shader::createProgram(const std::string& vertexShader, const std::string& fragementShader)
{
    RenderId program = glCreateProgram();
    RenderId vs = compireShader(GL_VERTEX_SHADER, vertexShader);
    RenderId fs = compireShader(GL_FRAGMENT_SHADER, fragementShader);
    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));
    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));
    return program;
}
