#include <Gl/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include "src/utils/utils.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"

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
    {
        std::vector<float> triangle = {
            -0.5f, -0.5f,
            0.5f, -0.5f,
            0.5f, 0.5f,
            -0.5f, 0.5f
        };
        std::vector<unsigned int> indices =
        {
            0,1,2,
            2,3,0
        };
        VertexArray vao;

        VertexBufferLayout layout;
        layout.push<float>(2);
        VertexBuffer vbo = VertexBuffer(triangle.data(), triangle.size() * sizeof(float));
        vao.addVertexBuffer(vbo, layout);
        IndexBuffer ibo = IndexBuffer(indices.data(), indices.size());
        ShaderProgram shader = praseShader("res/shaders/base.shader");
        unsigned int program = createShader(shader.vertexShader, shader.fragmantShader);
        unsigned int location = glGetUniformLocation(program, "u_Color");
        float r = 0.0f;
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);
            GLCall(glUseProgram(program));
            GLCall(glUniform4f(location, r, 0.25, 0.1, 1.0));
            vao.bind();
            ibo.bind();
            GLCall(glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_INT, nullptr));
            if (r >= 1.0f)
            {
                r -= 1.0f;
            }
            r += 0.05f;
            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}