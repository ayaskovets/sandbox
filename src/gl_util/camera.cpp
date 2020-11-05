#include "camera.hpp"

#include "glm/gtc/quaternion.hpp"

namespace gl_util
{

Camera::Camera(glm::vec3 pos, glm::vec3 front, glm::vec3 right, glm::vec3 up)
: pos(pos)
, front(front)
, right(right)
, up(up)
{}

Camera::Camera(glm::vec3 pos)
: Camera(pos, glm::vec3(0, 0, -1), glm::vec3(1, 0, 0), glm::vec3(0, 1, 0))
{}

Camera::Camera()
: Camera(glm::vec3(0, 0, 0))
{}

void Camera::move(CameraMoveDirection dir, GLfloat dist)
{
    switch (dir)
    {
    case CameraMoveDirection::Forward:  pos += front * dist; break;
    case CameraMoveDirection::Backward: pos -= front * dist; break;
    case CameraMoveDirection::Left:     pos -= right * dist; break;
    case CameraMoveDirection::Right:    pos += right * dist; break;
    case CameraMoveDirection::Up:       pos += up * dist;    break;
    case CameraMoveDirection::Down:     pos -= up * dist;    break;
    }
}

void Camera::rotate(CameraRotationDirection dir, GLfloat angle)
{
    switch (dir)
    {
    case CameraRotationDirection::Yaw:
        front = glm::normalize(front * glm::angleAxis(glm::radians(angle), up));
        right = glm::normalize(glm::cross(front, up));
        break;
    case CameraRotationDirection::Pitch:
        front = glm::normalize(front * glm::angleAxis(glm::radians(angle), -right));
        right = glm::normalize(glm::cross(front, up));
        break;
    case CameraRotationDirection::Roll:
        right = glm::normalize(right * glm::angleAxis(glm::radians(angle), -front));
        up = glm::normalize(glm::cross(right, front));
        break;
    }
}

glm::mat4 Camera::getView() const
{
    return glm::lookAt(pos, pos + front, up);
}

}
