#include "game.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace game
{

GLboolean key_pressed[GLFW_KEY_LAST];

Bird::Bird(gl_util::Model&& bird_model)
: model(std::forward<gl_util::Model>(bird_model))
, y_speed(0)
, tube_crashed(false)
, crashed(false)
{}

void Bird::update()
{
    if (!tube_crashed && key_pressed[GLFW_KEY_F])
    {
        y_speed = .13f;

        model.transform[0].x = glm::cos(glm::radians(30.f));
        model.transform[0].y = glm::sin(glm::radians(30.f));

        model.transform[1].x = -glm::sin(glm::radians(30.f));
        model.transform[1].y = glm::cos(glm::radians(30.f));
    }

    if (model.transform[3].y >= -3.4f)
    {
        model.transform[3].y += (y_speed -= .013f);
        model.transform = glm::rotate(model.transform, glm::radians(-3.f), glm::vec3(0, 0, 1));
    }
    else
    {
        crashed = true;
    }
}

}
