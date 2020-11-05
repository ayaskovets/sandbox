#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "util/mixin.hpp"

namespace gl_util
{

class Window : public util::NonCopyable
{
    GLFWwindow* handle;

public:
    Window(const GLchar* title, GLuint width, GLuint height, GLFWmonitor* mon);
    Window(Window&& window);
    Window& operator=(Window&& window) = delete;
    ~Window();

    GLboolean isOpen() const;

    GLint getWidth() const;
    GLint getHeight() const;

    void update() const;
    void close() const;

    void setCallback(GLFWframebuffersizefun) const;
    void setCallback(GLFWkeyfun) const;
    void setCallback(GLFWmousebuttonfun) const;
    void setCallback(GLFWcursorposfun) const;
};

}
