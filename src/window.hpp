#pragma once

#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "util.hpp"

class Window : public NonCopyMoveAble
{
    GLFWwindow* handle;

public:
    Window(const GLchar* title, GLuint width, GLuint height, GLFWmonitor* mon);
    ~Window();

    GLboolean isOpen() const;

    GLint getWidth() const;
    GLint getHeight() const;

    void update();
    void close();

    void setResizeCallback(GLFWframebuffersizefun callback);
    void setKeyCallback(GLFWkeyfun callback);
    void setMouseButtonCallback(GLFWmousebuttonfun callback);
    void setMouseMoveCallback(GLFWcursorposfun callback);
};
