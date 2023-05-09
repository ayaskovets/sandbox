#include "texture.hpp"

#define GLEW_STATIC
#include "GL/glew.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include "util/log.hpp"

namespace gl_util
{

Texture::Texture()
: GLobject()
, width(0)
, height(0)
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
}

Texture::Texture(const char* path)
: Texture()
{
    int channels = 0;
    stbi_set_flip_vertically_on_load(true);
    if (const auto data = stbi_load(path, &width, &height, &channels, 0))
    {
        GLint colorspace = GL_RGB;

        switch (channels)
        {
        case 3: colorspace = GL_RGB; break;
        case 4: colorspace = GL_RGBA; break;
        }

        glTexImage2D(GL_TEXTURE_2D, 0, colorspace, width, height, 0, colorspace, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    }
    else
    {
        util::log::cerr("Texture loading failed:", path);
    }
}

Texture::Texture(Texture&& texture)
: GLobject(texture.id)
{
    texture.id = 0;
    texture.width = 0;
    texture.height = 0;
}

GLint Texture::getWidth() const
{
    return width;
}

GLint Texture::getHeight() const
{
    return height;
}

void Texture::bind() const
{
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::unbind() const
{
    glBindTexture(GL_TEXTURE_2D, id);
}

}
