#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>
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
    void setUniform(const GLchar* name, const T& value) const
    {
        setUniform(glGetUniformLocation(id, name), value);
    }

    void setUniform(GLint location, const GLboolean& value) const;
    void setUniform(GLint location, const GLint& value) const;
    void setUniform(GLint location, const GLfloat& value) const;
    void setUniform(GLint location, const glm::vec2& value) const;
    void setUniform(GLint location, const glm::vec3& value) const;
    void setUniform(GLint location, const glm::vec4& value) const;
    void setUniform(GLint location, const glm::mat2& value) const;
    void setUniform(GLint location, const glm::mat3& value) const;
    void setUniform(GLint location, const glm::mat4& value) const;

};

}
