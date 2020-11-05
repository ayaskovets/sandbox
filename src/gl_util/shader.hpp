#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <utility>

#include "globject.hpp"

namespace gl_util
{

class Shader : public gl_util::GLobject
{
    GLenum type;

public:
    explicit Shader(GLenum type);
    Shader(Shader&& shader) noexcept;
    ~Shader();

    GLenum getType() const noexcept;

    GLboolean compileFromFile(const GLchar* shader_path) const;
    GLboolean compileFromCode(const GLchar* shader_code) const;
};

class ShaderProgram : public GLobject
{
public:
    static ShaderProgram FromShaderFileList(std::initializer_list<std::pair<GLint, const GLchar*>> shaders);

    ShaderProgram();
    ShaderProgram(ShaderProgram&& program) noexcept;
    ShaderProgram& operator=(ShaderProgram&& program) = delete;
    ~ShaderProgram();

    const ShaderProgram& attachShader(const Shader& shader) const;

    GLboolean link() const;
    void enable() const;
    void disable() const;

    template <typename T>
    void setUniform(const GLchar* name, const T& value) const;
    template <typename T>
    void setUniform(GLint location, const T& value) const;
};

}
