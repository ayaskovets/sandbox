#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "gl_util/model.hpp"

namespace game
{

extern GLboolean key_pressed[GLFW_KEY_LAST];
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (action == GLFW_RELEASE)
    {
        key_pressed[key] = GL_FALSE;
    }
    else if (action == GLFW_PRESS)
    {
        key_pressed[key] = GL_TRUE;
    }

    if (key_pressed[GLFW_KEY_ESCAPE])
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

struct Bird
{
    gl_util::Model model;
    GLfloat y_speed;

    bool tube_crashed;
    bool crashed;

    Bird(gl_util::Model&& bird_model);

    void update();
};

}
