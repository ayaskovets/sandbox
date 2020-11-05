#pragma once

#define GLEW_STATIC
#include "GL/glew.h"

#include "util.hpp"

class GLobject : NonCopyAble
{
protected:
    GLuint id;

    GLobject();
    explicit GLobject(GLuint ID);
    GLobject(GLobject&& object);
    GLobject& operator=(GLobject&& object);

public:
    GLuint getID() const;
};
