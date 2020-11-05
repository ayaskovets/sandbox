#include "shader.hpp"

#include <fstream>
#include <string>
#include <vector>

#include "util/log.hpp"

namespace gl_util
{

Shader::Shader(GLenum type)
: GLobject(glCreateShader(type))
, type(type)
{}

Shader::Shader(Shader&& shader) noexcept
: GLobject(shader.id)
, type(shader.type)
{
    shader.id = 0;
}

Shader::~Shader()
{
    glDeleteShader(id);
}

GLenum Shader::getType() const noexcept
{
    return type;
}

GLboolean Shader::compileFromFile(const GLchar* shader_path) const
{
    std::basic_ifstream<GLchar> ifs(shader_path, std::ios::binary);
    if (!ifs.is_open())
    {
        util::log::cerr("Failed to read shader:", shader_path);
        return GL_FALSE;
    }

    ifs.seekg(0, std::ios::end);
    std::basic_string<GLchar> shader_code(ifs.tellg(), '\0');
    ifs.seekg(0, std::ios::beg);

    ifs.read(shader_code.data(), shader_code.size());
    return compileFromCode(shader_code.c_str());
}

GLboolean Shader::compileFromCode(const GLchar* shader_code) const
{
    glShaderSource(id, 1, &shader_code, nullptr);
    glCompileShader(id);

    GLint success = GL_FALSE;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);

    if (success != GL_TRUE)
    {
        GLint log_size = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &log_size);
        std::basic_string<GLchar> log(log_size, '\0');

        glGetShaderInfoLog(id, log_size, nullptr, log.data());
        util::log::cerr("Failed to read shader:", log);
        return GL_FALSE;
    }

    return GL_TRUE;
}

ShaderProgram ShaderProgram::FromShaderFileList(std::initializer_list<std::pair<GLint, const GLchar*>> shaders)
{
    ShaderProgram program;
    for (const auto& info : shaders)
    {
        Shader shader(info.first);
        if (shader.compileFromFile(info.second))
        { program.attachShader(shader); }
    }
    program.link();

    return program;
}

ShaderProgram::ShaderProgram()
: GLobject(glCreateProgram())
{}

ShaderProgram::ShaderProgram(ShaderProgram&& program) noexcept
: GLobject(program.id)
{
    program.id = 0;
}

ShaderProgram::~ShaderProgram()
{
    GLsizei n_shaders = 0;
    glGetAttachedShaders(id, 0, &n_shaders, nullptr);

    if (n_shaders != 0)
    {
        std::vector<GLuint> shaders(n_shaders, 0);
        glGetAttachedShaders(id, n_shaders, nullptr, shaders.data());
        for (const auto shader : shaders)
        {
            glDetachShader(id, shader);
        }
    }

    glDeleteProgram(id);
}

const ShaderProgram& ShaderProgram::attachShader(const Shader& shader) const
{
    glAttachShader(id, shader.getID());
    return *this;
}

GLboolean ShaderProgram::link() const
{
    glLinkProgram(id);

    GLint success = GL_FALSE;
    glGetProgramiv(id, GL_LINK_STATUS, &success);

    if (success != GL_TRUE)
    {
        GLint log_size = 0;
        glGetProgramiv(id, GL_INFO_LOG_LENGTH, &log_size);
        std::basic_string<GLchar> log(log_size, '\0');

        glGetProgramInfoLog(id, log_size, nullptr, log.data());
        util::log::cerr("Failed to link shader program:", log);
        return GL_FALSE;
    }

    return GL_TRUE;
}

void ShaderProgram::enable() const
{
    glUseProgram(id);
}

void ShaderProgram::disable() const
{
    glUseProgram(0);
}

void ShaderProgram::setUniform(GLint location, const GLboolean& value) const
{
    glUniform1i(location, static_cast<GLint>(value));
}
void ShaderProgram::setUniform(GLint location, const GLint& value) const
{
    glUniform1i(location, value);
}
void ShaderProgram::setUniform(GLint location, const GLfloat& value) const
{
    glUniform1f(location, value);
}
void ShaderProgram::setUniform(GLint location, const glm::vec2& value) const
{
    glUniform2fv(location, 1, &value[0]);
}
void ShaderProgram::setUniform(GLint location, const glm::vec3& value) const
{
    glUniform3fv(location, 1, &value[0]);
}
void ShaderProgram::setUniform(GLint location, const glm::vec4& value) const
{
    glUniform4fv(location, 1, &value[0]);
}
void ShaderProgram::setUniform(GLint location, const glm::mat2& value) const
{
    glUniformMatrix2fv(location, 1, GL_FALSE, &value[0][0]);
}
void ShaderProgram::setUniform(GLint location, const glm::mat3& value) const
{
    glUniformMatrix3fv(location, 1, GL_FALSE, &value[0][0]);
}
void ShaderProgram::setUniform(GLint location, const glm::mat4& value) const
{
    glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
}

}
