#include "window.hpp"

#include <iostream>

Window::Window(const GLchar* title, GLuint width, GLuint height, GLFWmonitor* mon)
: handle(nullptr)
{
    handle = glfwCreateWindow(width, height, title, mon, nullptr);
    if (!handle)
    {
        std::cerr << "Failed to create window: '" << title << "'" << std::endl;
    }
    else
    {
        glfwMakeContextCurrent(handle);
    }
}

Window::~Window()
{
    glfwSetWindowShouldClose(handle, GL_TRUE);
    glfwDestroyWindow(handle);
}

GLboolean Window::isOpen() const
{
    return handle && glfwWindowShouldClose(handle) == GLFW_FALSE;
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

void Window::update()
{
    glfwSwapBuffers(handle);
}

void Window::close()
{
    glfwSetWindowShouldClose(handle, GL_TRUE);
}

void Window::setResizeCallback(GLFWframebuffersizefun callback)
{
    glfwSetFramebufferSizeCallback(handle, callback);
}

void Window::setKeyCallback(GLFWkeyfun callback)
{
    glfwSetKeyCallback(handle, callback);
}

void Window::setMouseButtonCallback(GLFWmousebuttonfun callback)
{
    glfwSetMouseButtonCallback(handle, callback);
}

void Window::setMouseMoveCallback(GLFWcursorposfun callback)
{
    glfwSetCursorPosCallback(handle, callback);
}
