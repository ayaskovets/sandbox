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

GLobject& GLobject::operator=(GLobject&& object)
{
    id = object.id;
    object.id = 0;
    return *this;
}

GLuint GLobject::getID() const
{
    return id;
}
