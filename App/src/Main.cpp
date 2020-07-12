#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Context.h"
#include "shaders/ShaderLoader.h"

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

GLboolean wireframe = GL_FALSE;

int main()
{
    Context ctx;
    glfwSetKeyCallback(ctx.getWindow(), key_callback);

    // build and compile our shader program
    // ------------------------------------
    ShaderLoader TriangleShader("src/shaders/Triangle.vert", "src/shaders/Triangle.frag");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertexPositions[] = {
        // first triangle
        -0.9f, -0.5f, 0.0f,  1.0f,  0.0f, 0.0f,  // left 
        -0.0f, -0.5f, 0.0f,  0.0f,  1.0f, 0.0f,  // right
        -0.45f, 0.5f, 0.0f,  0.0f,  0.0f, 1.0f,  // top 
        // second triangle
         0.0f, -0.5f, 0.0f, 0.0f,  0.0f, 1.0f,  // left
         0.9f, -0.5f, 0.0f, 1.0f,  0.0f, 0.0f,  // right
         0.45f, 0.5f, 0.0f, 0.0f,  1.0f, 0.0f   // top 
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);


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

        // draw our first triangle
        TriangleShader.use();
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // glBindVertexArray(0); // no need to unbind it every time 

        // Swap the screen buffers
        glfwSwapBuffers(ctx.getWindow());
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
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
            wireframe ^= GL_TRUE;
        }
    }
}