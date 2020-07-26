#pragma once

#include <GLFW/glfw3.h>
#include <iostream>

#include "renderer/Camera.h"

bool WIREFRAME = false;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = 800 / 2.0f;
float lastY = 600 / 2.0f;
bool firstMouse = true;

extern double deltaTime;

inline void key_callback(GLFWwindow* window, const int key, int scancode, const int action, int mode)
{
    std::cout << "Key: " << key << " - Action: " << action << std::endl;
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_ESCAPE)
            glfwSetWindowShouldClose(window, GL_TRUE);

        if (key == GLFW_KEY_SPACE) {
            glPolygonMode(GL_FRONT_AND_BACK, WIREFRAME ? GL_FILL : GL_LINE);
            WIREFRAME = !WIREFRAME;
        }
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.process_keyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.process_keyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.process_keyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.process_keyboard(RIGHT, deltaTime);
}

inline void mouse_callback(GLFWwindow* window, const double xpos, const double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    const auto xoffset = xpos - lastX;
    const auto yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.process_mouse_movement(xoffset, yoffset);
}