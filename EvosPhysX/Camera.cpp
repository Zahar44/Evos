
#include "Camera.h"

void Camera::updateView(const glm::vec3& position)
{
    glm::vec3 eye = { position.x, position.y + zoom, position.z + zoom };
    view = glm::lookAt(eye, position + orientation, up);
}

void Camera::updateProjection()
{
    projection = glm::perspective(glm::radians(fov), windowSize.getRatio(), nearPlane, farPlane);
    auto size = windowSize.getSize();
    oprojection = glm::ortho(0.0f, (float)size.x, 0.0f, (float)size.y);
}

void Camera::processMouseScroll(double yoffset)
{
    zoom -= (float)yoffset * zoomPower;
}

void Camera::processMouseMovement(double xoffset, double yoffset)
{
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    glm::vec3 newOrientation = glm::rotate(
        orientation, glm::radians((float)-yoffset), glm::normalize(glm::cross(orientation, up)));
    // Adjust the orientation based on the mouse movement
    orientation += glm::vec3(yoffset, xoffset, 0.0f);

    // Decides whether or not the next vertical Orientation is legal or not
    if (abs(glm::angle(newOrientation, up) - glm::radians(90.0f)) <= glm::radians(85.0f))
    {
        orientation = newOrientation;
    }

    // Rotates the Orientation left and right
    orientation = glm::rotate(orientation, glm::radians((float)-xoffset), up);
}
