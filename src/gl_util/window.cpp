#include "window.hpp"

#include "util/log.hpp"

namespace gl_util
{

Window::Window(const GLchar* title, GLuint width, GLuint height, GLFWmonitor* mon)
: handle(glfwCreateWindow(width, height, title, mon, nullptr))
{
    if (!handle)
    {
        util::log::cerr("Failed to create window:", title);
    }

    glfwMakeContextCurrent(handle);
}

Window::Window(Window&& window)
: handle(window.handle)
{
    window.handle = nullptr;
}

Window::~Window()
{
    glfwSetWindowShouldClose(handle, GL_TRUE);
    glfwDestroyWindow(handle);
}

GLboolean Window::isOpen() const
{
    return handle && glfwWindowShouldClose(handle) != GLFW_TRUE;
}

GLint Window::getWidth() const
{
    GLint width = 0;
    glfwGetWindowSize(handle, &width, nullptr);
    return width;
}

GLint Window::getHeight() const
{
    GLint height = 0;
    glfwGetWindowSize(handle, nullptr, &height);
    return height;
}

void Window::update() const
{
    glfwSwapBuffers(handle);
}

void Window::close() const
{
    glfwSetWindowShouldClose(handle, GL_TRUE);
}

template <>
void Window::setCallback(GLFWframebuffersizefun callback) const
{
    glfwSetFramebufferSizeCallback(handle, callback);
}
template <>
void Window::setCallback(GLFWkeyfun callback) const
{
    glfwSetKeyCallback(handle, callback);
}
template <>
void Window::setCallback(GLFWmousebuttonfun callback) const
{
    glfwSetMouseButtonCallback(handle, callback);
}
template <>
void Window::setCallback(GLFWcursorposfun callback) const
{
    glfwSetCursorPosCallback(handle, callback);
}

}
