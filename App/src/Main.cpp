#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "Context.h"
#include "shaders/ShaderLoader.h"
#include "renderer/Texture.h"


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

bool wireframe = false;

int main()
{
    Context ctx;
    glfwSetKeyCallback(ctx.getWindow(), key_callback);

    ShaderLoader TriangleShader("src/shaders/Triangle.vert", "src/shaders/Triangle.frag");


    float vertexPositions[] = {
        -0.9f, -0.5f, 0.0f,  1.0f,  0.0f, 0.0f,   0.0f, 0.0f, // bot left 
        -0.1f, -0.5f, 0.0f,  0.0f,  1.0f, 0.0f,   1.0f, 0.0f, // bot right
        -0.9f,  0.5f, 0.0f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f, // top left
        -0.1f,  0.5f, 0.0f,  1.0f,  1.0f, 1.0f,   1.0f, 1.0f, // top right

         0.9f, -0.5f, 0.0f,  1.0f,  0.0f, 0.0f,   0.0f, 0.0f, // bot left 
         0.1f, -0.5f, 0.0f,  0.0f,  1.0f, 0.0f,   1.0f, 0.0f, // bot right
         0.9f,  0.5f, 0.0f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f, // top left
         0.1f,  0.5f, 0.0f,  1.0f,  1.0f, 1.0f,   1.0f, 1.0f  // top right
    };

    unsigned int indices[] = {  
    0, 1, 3,   // first triangle
    3, 2, 0,    // second triangle
    4, 5, 7,
    7, 6, 4
    };

    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    Texture Tex1("res/tex1.png");
    

    // render loop
    // -----------
    while (!glfwWindowShouldClose(ctx.getWindow()))
    {
        // Check if any events have been activated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();

        // Render
        // Clear the colorbuffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        TriangleShader.use();
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::rotate(trans, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
        TriangleShader.setMat4("transform", &trans);
        
        Tex1.bind();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

        // Swap the screen buffers
        glfwSwapBuffers(ctx.getWindow());
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    // Terminates GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (action == GLFW_PRESS) {
        std::cout << key << std::endl;
        if (key == GLFW_KEY_ESCAPE)
            glfwSetWindowShouldClose(window, GL_TRUE);
        
        if (key == GLFW_KEY_SPACE) {
            glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_FILL : GL_LINE);
            wireframe = !wireframe;
        }
    }
}