#include "Camera.h"

Camera::Camera(glm::vec3 pos)
    : movementSpeed(SPEED)
	, mouseSensitivity(SENSITIVITY)
{
    position = pos;
    orientation = glm::quat(0, 0, 0, -1);
    rightAngle = 0.f;
    upAngle = 0.f;
    update_camera_vectors();
}

Camera::Camera(float posX, float posY, float posZ)
    : movementSpeed(SPEED)
	, mouseSensitivity(SENSITIVITY)
{
    position = glm::vec3(posX, posY, posZ);
    orientation = glm::quat(0, 0, 0, -1);
    rightAngle = 0.f;
    upAngle = 0.f;
    update_camera_vectors();
}

glm::mat4 Camera::GetViewMatrix() const
{
    glm::quat reverseOrient = glm::conjugate(orientation);
    glm::mat4 rot = glm::mat4_cast(reverseOrient);
    glm::mat4 translation = glm::translate(glm::mat4(1.0), -position);

    return rot * translation;
}

void Camera::process_keyboard(CamMov direction, float deltaTime)
{
    float velocity = movementSpeed * deltaTime;

    glm::quat qF = orientation * glm::quat(0, 0, 0, -1) * glm::conjugate(orientation);
    glm::vec3 Front = { qF.x, qF.y, qF.z };
    glm::vec3 Right = glm::normalize(glm::cross(Front, glm::vec3(0, 1, 0)));

    if (direction == CamMov::FORWARD)
        position += Front * velocity;
    if (direction == CamMov::BACKWARD)
        position -= Front * velocity;
    if (direction == CamMov::LEFT)
        position -= Right * velocity;
    if (direction == CamMov::RIGHT)
        position += Right * velocity;
}

void Camera::process_mouse_movement(float xoffset, float yoffset, bool constrainPitch)
{
	// TODO implement constrainPitch for quaternion camera
	
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    rightAngle += xoffset;
    upAngle += yoffset;

    update_camera_vectors();
}

void Camera::update_camera_vectors()
{
    // Yaw
    glm::quat aroundY = glm::angleAxis(glm::radians(-rightAngle), glm::vec3(0, 1, 0));

    // Pitch
    glm::quat aroundX = glm::angleAxis(glm::radians(upAngle), glm::vec3(1, 0, 0));

    orientation = aroundY * aroundX;
}