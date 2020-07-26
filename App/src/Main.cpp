#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "Context.h"
#include "MockData.h"

#include "renderer/Shader.h"
#include "renderer/Texture.h"
#include "renderer/VertexArray.h"
#include "renderer/Buffer.h"

#include "UserInput.h"

// timing
double deltaTime = 0.0f;
double lastFrameTime = 0.0f;
// FPS counter
double previousFPSTime = 0.0f;
int frameCount = 0;

int main()
{
    const Context ctx;
    ctx.set_key_callback(key_callback);
    ctx.set_cursor_callback(mouse_callback);
	
    const Shader triangleShader("Triangle");

    const Texture tex1("res/tex1.png");

    const VertexArray vao;
    const Buffer buff;
    buff.set_vertex(vertices, sizeof(vertices));
    // position attribute
    vao.add_attrib(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    // color attribute
    vao.add_attrib(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    while (!glfwWindowShouldClose(ctx.get_window()))
    {

        const auto currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrameTime;
        lastFrameTime = currentFrame;
    	
        frameCount++;
        if (currentFrame - previousFPSTime >= 1.0)
        {
            std::cout << "FPS: " << frameCount/(currentFrame - previousFPSTime) << std::endl;

            frameCount = 0;
            previousFPSTime = currentFrame;
        }

        glfwPollEvents();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        auto model = glm::mat4(1.0f);
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

		auto view = camera.GetViewMatrix();

        auto projection =  glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

        triangleShader.use();
        triangleShader.set_mat4("model", &model);
        triangleShader.set_mat4("view", &view);
        triangleShader.set_mat4("proj", &projection);
    	
        tex1.bind();
        vao.bind();
        glDrawArrays(GL_TRIANGLES, 0, 36);
    	
        // Swap the screen buffers
        glfwSwapBuffers(ctx.get_window());
    }

    glfwTerminate();
    return 0;
}
