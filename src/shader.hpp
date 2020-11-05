#pragma once

#include "GLutil.hpp"

class Shader : public GLobject
{
    GLint type;

public:
    explicit Shader(GLint tp);
    Shader(Shader&& shader);
    ~Shader();

    GLint getType() const;

    GLboolean compileFromFile(const GLchar* shader_path);
    GLboolean compileFromCode(const GLchar* shader_code);
};

#include "glm/glm.hpp"

#include <utility>

class ShaderProgram : public GLobject
{
public:
    static ShaderProgram FromShaderFileList(std::initializer_list<std::pair<GLint, const GLchar*>> shaders);

    ShaderProgram();
    ShaderProgram(ShaderProgram&& program);
    ShaderProgram& operator=(ShaderProgram&& program) = delete;
    ~ShaderProgram();

    const ShaderProgram& attachShader(const Shader& shader) const;

    GLboolean link() const;
    void enable() const;
    void disable() const;

    void setBool(const GLchar* uniform, GLboolean value) const;
    void setInt(const GLchar* uniform, GLint value) const;
    void setFloat(const GLchar* uniform, GLfloat value) const;

    void setVec2(const GLchar* uniform, const glm::vec2& value) const;
    void setVec2(const GLchar* uniform, GLfloat x, GLfloat y) const;

    void setVec3(const GLchar* uniform, const glm::vec3& value) const;
    void setVec3(const GLchar* uniform, GLfloat x, GLfloat y, GLfloat z) const;

    void setVec4(const GLchar* uniform, const glm::vec4& value) const;
    void setVec4(const GLchar* uniform, GLfloat x, GLfloat y, GLfloat z, GLfloat w) const;

    void setMat2(const GLchar* uniform, const glm::mat2& mat) const;
    void setMat3(const GLchar* uniform, const glm::mat3& mat) const;
    void setMat4(const GLchar* uniform, const glm::mat4& mat) const;
};
