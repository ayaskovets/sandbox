#include "vao.hpp"

VAO::VAO()
: GLobject()
{
    glGenVertexArrays(1, &id);
    glBindVertexArray(id);
}

VAO::VAO(VAO&& vao)
: GLobject(vao.id)
{
    vao.id = 0;
}

VAO::~VAO()
{
    glDeleteVertexArrays(1, &id);
}

void VAO::enableAttribute(GLuint index) const
{
    glEnableVertexAttribArray(index);
}

void VAO::disableAttribute(GLuint index) const
{
    glDisableVertexAttribArray(index);
}

void VAO::bind() const
{
    glBindVertexArray(id);
}

void VAO::unbind() const
{
    glBindVertexArray(0);
}

void VAO::setAttribute(GLuint index, GLint size, GLenum type,
    GLboolean normalized, GLsizei stride, const void* pointer) const
{
    glBindVertexArray(id);
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
    glEnableVertexAttribArray(index);
}
