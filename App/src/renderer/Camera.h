#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

enum class CamMov {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const float SPEED = 2.5f;
const float SENSITIVITY = 0.01f;

class Camera
{
public:
    Camera(glm::vec3 pos = glm::vec3(0.f, 0.f, 0.f));
    Camera(float posX, float posY, float posZ);

    glm::mat4 GetViewMatrix() const;
    void process_keyboard(CamMov direction, float deltaTime);
    void process_mouse_movement(float xoffset, float yoffset, bool constrainPitch = false);

private:
    glm::vec3 position;
    glm::quat orientation;
    float rightAngle;
    float upAngle;
    // Camera options
    float movementSpeed;
    float mouseSensitivity;
	
    void update_camera_vectors();
};
#endif