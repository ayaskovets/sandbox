#include "shader.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

Shader::Shader(GLint Type)
: GLobject(glCreateShader(Type))
, type(Type)
{}

Shader::Shader(Shader&& shader)
: GLobject(shader.id)
, type(shader.type)
{
    shader.id = 0;
}

Shader::~Shader()
{
    glDeleteShader(id);
}

GLint Shader::getType() const
{
    return type;
}

GLboolean Shader::compileFromFile(const GLchar* shader_path)
{
    std::basic_ifstream<GLchar> ifs(shader_path, std::ios::binary);
    if (!ifs.is_open())
    {
        std::cerr << "Failed to read shader: '" << shader_path << "'" << std::endl;
        return GL_FALSE;
    }

    ifs.seekg(0, std::ios::end);
    std::basic_string<GLchar> shader_code(ifs.tellg(), '\0');
    ifs.seekg(0, std::ios::beg);

    ifs.read(shader_code.data(), shader_code.size());

    return compileFromCode(shader_code.c_str());
}

GLboolean Shader::compileFromCode(const GLchar* shader_code)
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
        std::cerr << "Failed to compile shader: '" << log << "'" << std::endl;
        return GL_FALSE;
    }

    return GL_TRUE;
}

#include <vector>

ShaderProgram ShaderProgram::FromShaderFileList(std::initializer_list<std::pair<GLint, const GLchar*>> shaders)
{
    ShaderProgram program;
    for (const auto& shader_info : shaders)
    {
        Shader shader(shader_info.first);
        if (!shader.compileFromFile(shader_info.second))
        {
            break;
        }

        program.attachShader(shader);
    }
    program.link();

    return program;
}

ShaderProgram::ShaderProgram()
: GLobject(glCreateProgram())
{}

ShaderProgram::ShaderProgram(ShaderProgram&& program)
: GLobject(program.id)
{
    program.id = 0;
}


ShaderProgram::~ShaderProgram()
{
    GLsizei num_shaders = 0;
    glGetAttachedShaders(id, 0, &num_shaders, nullptr);

    if (num_shaders != 0)
    {
        std::vector<GLuint> shaders(num_shaders, 0);
        glGetAttachedShaders(id, num_shaders, nullptr, shaders.data());
        for (auto& shader : shaders)
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
        std::cerr << "Failed to link shader program: '" << log << "'" << std::endl;
        return GL_FALSE;
    }

    return GL_TRUE;
}

void ShaderProgram::setBool(const GLchar* uniform, GLboolean value) const
{
    glUniform1i(glGetUniformLocation(id, uniform), (GLint)value);
}

void ShaderProgram::setInt(const GLchar* uniform, GLint value) const
{
    glUniform1i(glGetUniformLocation(id, uniform), value);
}

void ShaderProgram::setFloat(const GLchar* uniform, GLfloat value) const
{
    glUniform1f(glGetUniformLocation(id, uniform), value);
}

void ShaderProgram::setVec2(const GLchar* uniform, const glm::vec2 &value) const
{
    glUniform2fv(glGetUniformLocation(id, uniform), 1, &value[0]);
}

void ShaderProgram::setVec2(const GLchar* uniform, GLfloat x, GLfloat y) const
{
    glUniform2f(glGetUniformLocation(id, uniform), x, y);
}

void ShaderProgram::setVec3(const GLchar* uniform, const glm::vec3& value) const
{
    glUniform3fv(glGetUniformLocation(id, uniform), 1, &value[0]);
}

void ShaderProgram::setVec3(const GLchar* uniform, GLfloat x, GLfloat y, GLfloat z) const
{
    glUniform3f(glGetUniformLocation(id, uniform), x, y, z);
}

void ShaderProgram::setVec4(const GLchar* uniform, const glm::vec4& value) const
{
    glUniform4fv(glGetUniformLocation(id, uniform), 1, &value[0]);
}

void ShaderProgram::setVec4(const GLchar* uniform, GLfloat x, GLfloat y, GLfloat z, GLfloat w) const
{
    glUniform4f(glGetUniformLocation(id, uniform), x, y, z, w);
}

void ShaderProgram::setMat2(const GLchar* uniform, const glm::mat2& mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(id, uniform), 1, GL_FALSE, &mat[0][0]);
}

void ShaderProgram::setMat3(const GLchar* uniform, const glm::mat3& mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(id, uniform), 1, GL_FALSE, &mat[0][0]);
}

void ShaderProgram::setMat4(const GLchar* uniform, const glm::mat4& mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(id, uniform), 1, GL_FALSE, &mat[0][0]);
}

void ShaderProgram::enable() const
{
    glUseProgram(id);
}

void ShaderProgram::disable() const
{
    glUseProgram(0);
}
