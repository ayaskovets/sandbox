#pragma once

#include <memory>
#include <vector>

#include "glm/mat4x4.hpp"

#include "mesh.hpp"
#include "texture.hpp"

namespace gl_util
{

struct Asset
{
    std::shared_ptr<Mesh> mesh;
    std::shared_ptr<Texture> texture;
};

struct Model
{
    static Model FromAssetList(std::initializer_list<std::shared_ptr<Asset>> assets);

    std::vector<std::shared_ptr<Asset>> assets;
    glm::mat4 transform;

    Model();

    void draw() const;
};

}
