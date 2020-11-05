#include "globject.hpp"

namespace gl_util
{

GLobject::GLobject(GLuint id) noexcept
: id(id)
{}

GLobject::GLobject(GLobject&& object) noexcept
: GLobject(object.id)
{
    object.id = 0;
}

GLuint GLobject::getID() const noexcept
{
    return id;
}

}
