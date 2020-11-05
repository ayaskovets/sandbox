#pragma once

#include "globject.hpp"

namespace gl_util
{

template <GLint T>
class Buffer : public GLobject
{
private:
    GLsizeiptr size;

public:
    Buffer();
    Buffer(const void* data, GLsizeiptr size, GLenum usage);
    Buffer(Buffer&& buffer);
    Buffer& operator=(Buffer&& buffer) = delete;
    ~Buffer();

    constexpr GLint getType() const
    {
        return T;
    }

    GLsizeiptr getSize() const;

    void bind() const;
    void unbind() const;

    void setData(const void* data, GLsizeiptr size, GLenum usage);
};

using ArrayBuffer = Buffer<GL_ARRAY_BUFFER>;
using IndexBuffer = Buffer<GL_ELEMENT_ARRAY_BUFFER>;

}
