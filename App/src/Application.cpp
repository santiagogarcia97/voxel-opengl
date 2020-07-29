#include "Application.h"

#include "MockData.h"
#include "UserInput.h"

Application::Application()
	: triangleShader("Triangle")
	, tex1("res/tex1.png")
{
    ctx.set_key_callback(key_callback);
    ctx.set_cursor_callback(mouse_callback);

    buff.set_vertex(vertices, sizeof(vertices));
    // position attribute
    vao.add_attrib(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    // color attribute
    vao.add_attrib(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
}

Application::~Application()
{
	glfwTerminate();
}

int Application::run()
{
	// Game loop
    while (!glfwWindowShouldClose(ctx.get_window()))
    {
        timer.update();

        glfwPollEvents();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        auto model = glm::mat4(1.0f);
        //model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        auto view = camera.GetViewMatrix();
        auto projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

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
	
    return 0;
}
