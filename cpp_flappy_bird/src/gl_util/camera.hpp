#pragma once

#define GLEW_STATIC
#include "GL/glew.h"

#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"

namespace gl_util
{

enum class CameraMoveDirection
{
    Forward,
    Backward,
    Left,
    Right,
    Up,
    Down
};

enum class CameraRotationDirection
{
    Yaw,
    Pitch,
    Roll
};

class Camera
{
    glm::vec3 pos;

    glm::vec3 front;
    glm::vec3 right;
    glm::vec3 up;

public:
    Camera(glm::vec3 Pos, glm::vec3 Front, glm::vec3 Right, glm::vec3 Up);
    explicit Camera(glm::vec3 Pos);
    Camera();

    void move(CameraMoveDirection dir, GLfloat dist);
    void rotate(CameraRotationDirection dir, GLfloat angle);

    glm::mat4 getView() const;
};

}
