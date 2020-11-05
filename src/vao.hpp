#pragma once

#include "GLutil.hpp"

class VertexArray : public GLobject
{
public:
    VertexArray();
    VertexArray(VertexArray&& vao);
    VertexArray& operator=(VertexArray&& vao) = delete;
    ~VertexArray();

    void enableAttribute(GLuint index) const;
    void disableAttribute(GLuint index) const;

    void bind() const;
    void unbind() const;

    void setAttribute(GLuint index, GLint size, GLenum type,
        GLboolean normalized, GLsizei stride, const void* pointer) const;
};