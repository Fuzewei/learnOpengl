#include <Gl/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <memory>
#include "src/utils/utils.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Editor/Editor.h"
#include "World.h"
#include "Object.h"
#include "Components/Image.h"
#include "Components/Transform.h"



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
        Editor editor(window);
        std::vector<float> triangle = {
            -50.0f, -50.0f,0.0f,0.0f,
            50.0f, -50.0f, 1.0f,0.0f,
            50.0f, 50.0f, 1.0f,1.0f,
           -50.0f,50.0f,0.0f,1.0f
        };
        std::vector<unsigned int> indices =
        {
            0,1,2,
            2,3,0
        };
        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        VertexArray vao;
        VertexBufferLayout layout;
        layout.push<float>(2);
        layout.push<float>(2);
        VertexBuffer vbo = VertexBuffer(triangle.data(), triangle.size() * sizeof(float));
        vao.addVertexBuffer(vbo, layout);
        IndexBuffer ibo = IndexBuffer(indices.data(), indices.size());
        Shader shader = Shader("res/shaders/base.shader");
        glm::mat4x4 viex = glm::translate(glm::mat4(1), glm::vec3(0.5f, 0.4, 0.2));
        glm::mat4x4 proj = glm::ortho<float>(-100.0f, 100.0f, -100.0f, 100.0f, -1.0f, 1.0f);

        Renderer renderer;
        Texture texture("res/Texture/test.png");
        float r = 0.0f;

        bool show_demo_window = true;
        bool show_another_window = false;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        World& world = World::getInstance();
        auto obj = std::make_shared<Object>();
        auto im = std::make_shared<Image>();
        auto transform = std::make_shared<Transform>();
        obj->addComponent(im);
        obj->addComponent(transform);
        world.addObject(obj);
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            ImGui_ImplGlfwGL3_NewFrame();
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);
            world.Tick();


            glm::vec3 trans(0);
            ImGui::Begin("ahah");
            ImGui::SliderFloat3("float", &trans.x, -100, 100);
            ImGui::End();
            glm::mat4x4 model = glm::translate(glm::mat4(1), trans);



            texture.bind();
            shader.bind();
            shader.setUniform1i("u_Texture", 0);
            shader.setUniformMat4f("u_MVP", proj * viex * model);
            shader.setUniform4f("u_Color", r, 0.25, 0.1, 1.0);
            renderer.draw(vao, ibo, shader);
            if (r >= 1.0f)
            {
                r -= 1.0f;
            }
            r += 0.05f;


            //{
            //    static float f = 0.0f;
            //    static int counter = 0;
            //    ImGui::Text("Hello, world!");                           // Display some text (you can use a format string too)
            //    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f    
            //    ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            //    ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our windows open/close state
            //    ImGui::Checkbox("Another Window", &show_another_window);

            //    if (ImGui::Button("Button"))                            // Buttons return true when clicked (NB: most widgets return true when edited/activated)
            //        counter++;
            //    ImGui::SameLine();
            //    ImGui::Text("counter = %d", counter);

            //    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            //}
            ImGui::Render();
            ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}