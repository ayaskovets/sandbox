#pragma once

#include "glm/glm.hpp"

#include "buffer.hpp"
#include "util.hpp"
#include "vao.hpp"

struct Vertex
{
    glm::vec3 pos;
    glm::vec2 texcoord;
};

class Mesh : NonCopyMoveAble
{
    VertexArray vao;
    ArrayBuffer vbo;
    IndexBuffer ibo;

public:
    Mesh();
    Mesh(const Vertex* Vertices, GLsizeiptr Vsize, const GLushort* Indices, GLsizeiptr Isize);

    void draw() const;
};
