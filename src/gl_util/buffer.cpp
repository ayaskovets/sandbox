#include "buffer.hpp"

namespace gl_util
{

template <GLint T>
Buffer<T>::Buffer()
: GLobject()
, size(0)
{
    glGenBuffers(1, &id);
    glBindBuffer(T, id);
}

template <GLint T>
Buffer<T>::Buffer(const void* data, GLsizeiptr size, GLenum usage)
: Buffer()
, size(size)
{
    glBufferData(T, size, data, usage);
}

template <GLint T>
Buffer<T>::Buffer(Buffer&& buffer)
: GLobject(buffer.id)
{
    buffer.id = 0;
}

template <GLint T>
Buffer<T>::~Buffer()
{
    glDeleteBuffers(1, &id);
}

template <GLint T>
GLsizeiptr Buffer<T>::getSize() const
{
    return size;
}

template <GLint T>
void Buffer<T>::bind() const
{
    glBindBuffer(T, id);
}

template <GLint T>
void Buffer<T>::unbind() const
{
    glBindBuffer(T, 0);
}

template <GLint T>
void Buffer<T>::setData(const void* data, GLsizeiptr size, GLenum usage)
{
    this->size = size;
    glBindBuffer(T, id);
    glBufferData(T, size, data, usage);
}

}
