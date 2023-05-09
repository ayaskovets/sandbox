#include "mesh.hpp"

namespace gl_util
{

Mesh::Mesh()
: vao()
, vbo()
, ibo()
{
    vao.setAttribute(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
    vao.setAttribute(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, texcoord));
}

Mesh::Mesh(const Vertex* Vertices, GLsizeiptr Vsize, const GLushort* Indices, GLsizeiptr Isize)
: Mesh()
{
    vbo.setData(Vertices, Vsize, GL_STATIC_DRAW);
    ibo.setData(Indices, Isize, GL_STATIC_DRAW);
}

void Mesh::draw() const
{
    vao.bind();
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(ibo.getSize() / sizeof(GLushort)), GL_UNSIGNED_SHORT, nullptr);
}

}
