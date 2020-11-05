#pragma once

#include "globject.hpp"

class VAO : public gl_util::GLobject
{
public:
    VAO();
    VAO(VAO&& vao);
    VAO& operator=(VAO&& vao) = delete;
    ~VAO();

    void enableAttribute(GLuint index) const;
    void disableAttribute(GLuint index) const;

    void bind() const;
    void unbind() const;

    void setAttribute(GLuint index, GLint size, GLenum type,
        GLboolean normalized, GLsizei stride, const void* pointer) const;
};