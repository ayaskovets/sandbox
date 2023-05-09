#pragma once

#include "gl_util/globject.hpp"

namespace gl_util
{

class Texture : public gl_util::GLobject
{
    GLint width;
    GLint height;

public:
    Texture();
    Texture(const char* path);
    Texture(Texture&& texture);
    Texture& operator=(Texture&& texture) = delete;

    GLint getWidth() const;
    GLint getHeight() const;

    void bind() const;
    void unbind() const;
};

}
