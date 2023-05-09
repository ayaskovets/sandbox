#include "model.hpp"

#include "glm/gtc/matrix_transform.hpp"

namespace gl_util
{

Model Model::FromAssetList(std::initializer_list<std::shared_ptr<Asset>> assets)
{
    Model model;
    for (const auto& asset : assets)
    {
        model.assets.push_back(asset);
    }

    return model;
}

Model::Model()
: assets()
, transform(glm::identity<glm::mat4>())
{}

void Model::draw() const
{
    for (const auto& asset : assets)
    {
        asset->texture->bind();
        asset->mesh->draw();
    }
}

}
