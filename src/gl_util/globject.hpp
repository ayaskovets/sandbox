#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include "util/mixin.hpp"

namespace gl_util
{

class GLobject : public util::NonCopyable
{
protected:
    GLuint id;

    constexpr GLobject() noexcept;
    explicit GLobject(GLuint id) noexcept;
    GLobject(GLobject&& object) noexcept;
    GLobject& operator=(GLobject&& object) = delete;

public:
    GLuint getID() const noexcept;
};

}
