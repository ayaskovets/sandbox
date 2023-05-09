#pragma once

#include "glm/glm.hpp"

#include "gl_util/buffer.hpp"
#include "util/mixin.hpp"
#include "gl_util/vao.hpp"

namespace gl_util
{

struct Vertex
{
    glm::vec3 pos;
    glm::vec2 texcoord;
};

class Mesh : public util::NonCopyable, public util::NonMoveable
{
    gl_util::VAO vao;
    gl_util::ArrayBuffer vbo;
    gl_util::IndexBuffer ibo;

public:
    Mesh();
    Mesh(const Vertex* Vertices, GLsizeiptr Vsize, const GLushort* Indices, GLsizeiptr Isize);

    void draw() const;
};

}
