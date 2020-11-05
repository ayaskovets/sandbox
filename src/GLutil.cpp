#include "GLutil.hpp"

GLobject::GLobject()
: id(0)
{}

GLobject::GLobject(GLuint ID)
: id(ID)
{}

GLobject::GLobject(GLobject&& object)
{
    id = object.id;
    object.id = 0;
}

GLuint GLobject::getID() const
{
    return id;
}
