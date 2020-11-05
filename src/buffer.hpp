#pragma once

#include "GLutil.hpp"
#include "util.hpp"

template <GLint Type>
class Buffer : public GLobject
{
    GLsizeiptr size;

public:
    Buffer()
    : GLobject()
    , size(0)
    {
        glGenBuffers(1, &id);
        glBindBuffer(Type, id);
    }

    Buffer(const void* data, GLsizeiptr sz, GLenum usage)
    : Buffer()
    , size(sz)
    {
        glBufferData(Type, sz, data, usage);
    }

    constexpr GLint getType() const
    {
        return Type;
    }

    GLsizeiptr getSize() const
    {
        return size;
    }

    void bind() const
    {
        glBindBuffer(Type, id);
    }

    void unbind() const
    {
        glBindBuffer(Type, 0);
    }

    void setData(const void* data, GLsizeiptr sz, GLenum usage)
    {
        glBindBuffer(Type, id);
        glBufferData(Type, size, data, usage);

        size = sz;
    }

    ~Buffer()
    {
        glDeleteBuffers(1, &id);
    }
};

using ArrayBuffer = Buffer<GL_ARRAY_BUFFER>;
using IndexBuffer = Buffer<GL_ELEMENT_ARRAY_BUFFER>;
