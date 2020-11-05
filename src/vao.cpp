#include "vao.hpp"

#include <utility>

VertexArray::VertexArray()
: GLobject()
{
    glGenVertexArrays(1, &id);
    glBindVertexArray(id);
}

VertexArray::VertexArray(VertexArray&& vao)
: GLobject(std::forward<VertexArray>(vao))
{}

void VertexArray::enableAttribute(GLuint index) const
{
    glEnableVertexAttribArray(index);
}

void VertexArray::disableAttribute(GLuint index) const
{
    glDisableVertexAttribArray(index);
}

void VertexArray::bind() const
{
    glBindVertexArray(id);
}

void VertexArray::unbind() const
{
    glBindVertexArray(0);
}

void VertexArray::setAttribute(GLuint index, GLint size, GLenum type,
    GLboolean normalized, GLsizei stride, const void* pointer) const
{
    glBindVertexArray(id);
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
    glEnableVertexAttribArray(index);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &id);
}
