#pragma once

#define GLEW_STATIC
#include "GL/glew.h"

#include "globject.hpp"

namespace gl_util
{

template <GLint T>
class Buffer : public GLobject
{
private:
    GLsizeiptr size;

public:
    Buffer()
    : GLobject()
    , size(0)
    {
        glGenBuffers(1, &id);
        glBindBuffer(T, id);
    }

    Buffer(const void* data, GLsizeiptr size, GLenum usage)
    : Buffer()
    {
        this->size = size;
        glBufferData(T, size, data, usage);
    }

    Buffer(Buffer&& buffer)
    : GLobject(buffer.id)
    {
        buffer.id = 0;
    }

    Buffer& operator=(Buffer&& buffer) = delete;
    ~Buffer()
    {
        glDeleteBuffers(1, &id);
    }

    constexpr GLint getType() const
    {
        return T;
    }

    GLsizeiptr getSize() const
    {
        return size;
    }

    void bind() const
    {
        glBindBuffer(T, id);
    }

    void unbind() const
    {
        glBindBuffer(T, 0);
    }

    void setData(const void* data, GLsizeiptr size, GLenum usage)
    {
        this->size = size;
        glBindBuffer(T, id);
        glBufferData(T, size, data, usage);
    }
};

using ArrayBuffer = Buffer<GL_ARRAY_BUFFER>;
using IndexBuffer = Buffer<GL_ELEMENT_ARRAY_BUFFER>;

}
