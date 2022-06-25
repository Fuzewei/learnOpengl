#include <Gl/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

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

static ShaderProgram praseShader(const std::string &filePath)
{
    std::ifstream file(filePath);
    std::string line;
    ShaderType shaderType = ShaderType::NONE;
    std::stringstream ss[2];
    while(std::getline(file, line))
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

static unsigned int compireShader(int type, const std::string &source)
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
        char* message =(char *) alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Falied co compile:" << (type == GL_VERTEX_SHADER ? " vertex shader" : "fragement shader")
            << std::endl;
        std::cout << message << std::endl;
    }
    return id;
}


static unsigned int createShader(const std::string &vertexShader, const std::string &fragementShader )
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


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
        std::cout << "errr" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;
    float triangle[] =
    {
        -0.5f, -0.5f,
        0.0f, 0.5f,
        0.5f, -0.5f
    };

    GLuint bufferID;
    glGenBuffers(1, &bufferID);
    glBindBuffer(GL_ARRAY_BUFFER, bufferID);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), triangle, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    ShaderProgram shader = praseShader("res/shaders/base.shader");
    unsigned int program = createShader(shader.vertexShader, shader.fragmantShader);
    glUseProgram(program);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        
        glDrawArrays(GL_TRIANGLES, 0, 3);
      

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}