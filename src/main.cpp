#include <deque>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "game.hpp"
#include "gl_util/buffer.hpp"
#include "gl_util/camera.hpp"
#include "gl_util/mesh.hpp"
#include "gl_util/model.hpp"
#include "gl_util/shader.hpp"
#include "gl_util/texture.hpp"
#include "gl_util/vao.hpp"
#include "gl_util/window.hpp"
#include "util/log.hpp"

int main(int argc, char* argv[])
{
    using namespace game;
    using namespace gl_util;

    // glfw initialization
    {
        if (const int ret = glfwInit(); ret != GLFW_TRUE)
        {
            util::log::cerr("glfwInit() failed");
            return 1;
        }

        srand(static_cast<unsigned int>(glfwGetTime()));

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwSetErrorCallback([](int code, const char* msg) -> void
        { util::log::cerr("Error", code, msg); });
    }

    // window creation
    const auto window = gl_util::Window("Bird", 800, 600, nullptr);
    window.setCallback(game::key_callback);

    // glew initialization
    {
        glewExperimental = GL_TRUE;
        if (const GLenum ret = glewInit(); ret != GLEW_OK)
        {
            util::log::cerr("glewInit() ->", ret, "glGetError() ->", glGetError());
            return 1;
        }

        glEnable(GL_BLEND);
        glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);

        glEnable(GL_DEPTH_TEST);

        glfwSwapInterval(1);
    }

    // shader creation
    const auto program = gl_util::ShaderProgram::FromShaderFileList(
    {
        { GL_VERTEX_SHADER, "./resources/shaders/vertex.vert" },
        { GL_FRAGMENT_SHADER, "./resources/shaders/fragment.frag" }
    });

    // vertex creation
    constexpr Vertex v_backg[]
    {
        { glm::vec3(-1, 1, 0), glm::vec2(-2, 1) },
        { glm::vec3(-1, -1, 0), glm::vec2(-2, 0) },
        { glm::vec3(2, -1, 0), glm::vec2(4, 0) },
        { glm::vec3(2, 1, 0), glm::vec2(4, 1) }
    };
    constexpr GLushort i_backg[]
    { 0, 2, 1, 0, 2, 3 };

    constexpr Vertex v_ground[]
    {
        { glm::vec3(-1, 1, 0), glm::vec2(-2, 1) },
        { glm::vec3(-1, -1, 0), glm::vec2(-2, 0) },
        { glm::vec3(2, -1, 0), glm::vec2(4, 0) },
        { glm::vec3(2, 1, 0), glm::vec2(4, 1) }
    };
    constexpr GLushort i_ground[]
    { 0, 2, 1, 0, 2, 3 };

    constexpr Vertex v_bird[]
    {
        { glm::vec3(-0.5, 0.35, 0), glm::vec2(0, 1) },
        { glm::vec3(-0.5, -0.35, 0), glm::vec2(0, 0) },
        { glm::vec3(0.5, -0.35, 0), glm::vec2(1, 0) },
        { glm::vec3(0.5, 0.35, 0), glm::vec2(1, 1) }
    };
    constexpr GLushort i_bird[]
    { 0, 2, 1, 0, 2, 3 };

    constexpr Vertex v_tube_up[]
    {
        // body
        { glm::vec3(-0.5, 4, 0), glm::vec2(1.f / 26.f, 1) },
        { glm::vec3(-0.5, -2, 0), glm::vec2(1.f / 26.f, 12.f / 156.f) },
        { glm::vec3(0.5, -2, 0), glm::vec2(25.f / 26.f, 12.f / 156.f) },
        { glm::vec3(0.5, 4, 0), glm::vec2(25.f / 26.f, 1) },
        // top
        { glm::vec3(-26.f / 48.f, -2, 0), glm::vec2(0, 12.f / 156.f) },
        { glm::vec3(-26.f / 48.f, -2.5, 0), glm::vec2(0, 0) },
        { glm::vec3(26.f / 48.f, -2.5, 0), glm::vec2(1, 0) },
        { glm::vec3(26.f / 48.f, -2, 0), glm::vec2(1, 12.f / 156.f) }
    };
    constexpr GLushort i_tube_up[]
    { 0, 2, 1, 0, 2, 3, 4, 6, 5, 4, 6, 7 };

    constexpr Vertex v_tube_dn[]
    {
        // body
        { glm::vec3(-0.5, -2, 0), glm::vec2(1.f / 26.f, 144.f / 156.f) },
        { glm::vec3(-0.5, 4, 0), glm::vec2(1.f / 26.f, 12.f / 156.f) },
        { glm::vec3(0.5, 4, 0), glm::vec2(25.f / 26.f, 12.f / 156.f) },
        { glm::vec3(0.5, -2, 0), glm::vec2(25.f / 26.f, 144.f / 156.f) },
        // top
        { glm::vec3(-26.f / 48.f, 4.5, 0), glm::vec2(0, 1) },
        { glm::vec3(-26.f / 48.f, 4, 0), glm::vec2(0, 144.f / 156.f) },
        { glm::vec3(26.f / 48.f, 4, 0), glm::vec2(1, 144.f / 156.f) },
        { glm::vec3(26.f / 48.f, 4.5, 0), glm::vec2(1, 1) }
    };
    constexpr GLushort i_tube_dn[]
    { 0, 2, 1, 0, 2, 3, 4, 6, 5, 4, 6, 7 };

    // mesh creation
    const auto m_backg = std::make_shared<Mesh>(v_backg, sizeof(v_backg), i_backg, sizeof(i_backg));
    const auto m_tube_up = std::make_shared<Mesh>(v_tube_up, sizeof(v_tube_up), i_tube_up, sizeof(i_tube_up));
    const auto m_ground = std::make_shared<Mesh>(v_ground, sizeof(v_ground), i_ground, sizeof(i_ground));
    const auto m_bird = std::make_shared<Mesh>(v_bird, sizeof(v_bird), i_bird, sizeof(i_bird));
    const auto m_tube_dn = std::make_shared<Mesh>(v_tube_dn, sizeof(v_tube_dn), i_tube_dn, sizeof(i_tube_dn));

    // texture creation
    const auto t_backg_day = std::make_shared<Texture>("./resources/textures/background_day.png");
    const auto t_backg_ngt = std::make_shared<Texture>("./resources/textures/background_night.png");
    const auto t_ground_day = std::make_shared<Texture>("./resources/textures/ground_day.png");
    const auto t_ground_ngt = std::make_shared<Texture>("./resources/textures/ground_night.png");
    const auto t_bird_1 = std::make_shared<Texture>("./resources/textures/bird_1.png");
    const auto t_bird_2 = std::make_shared<Texture>("./resources/textures/bird_2.png");
    const auto t_bird_3 = std::make_shared<Texture>("./resources/textures/bird_3.png");
    const auto t_tube_up_day = std::make_shared<Texture>("./resources/textures/tube_up_day.png");
    const auto t_tube_dn_day = std::make_shared<Texture>("./resources/textures/tube_dn_day.png");
    const auto t_tube_up_ngt = std::make_shared<Texture>("./resources/textures/tube_up_night.png");
    const auto t_tube_dn_ngt = std::make_shared<Texture>("./resources/textures/tube_dn_night.png");

    // model creation
    Model backg = Model::FromAssetList({ std::make_shared<Asset>(Asset{ m_backg, t_backg_day }) });
    backg.transform = glm::translate(glm::scale(backg.transform, glm::vec3(15, 6, 1)), glm::vec3(0, 0.2, -10));

    Model ground = Model::FromAssetList({ std::make_shared<Asset>(Asset{ m_ground, t_ground_day }) });
    ground.transform = glm::translate(glm::scale(ground.transform, glm::vec3(20, 1.5, 1)), glm::vec3(0, -3.2, -8));

    Bird bird(Model::FromAssetList({ std::make_shared<Asset>(Asset{ m_bird, t_bird_1 }) }));
    bird.model.transform = glm::translate(bird.model.transform, glm::vec3(0, 1, -9.5));

    Model tube_up = Model::FromAssetList({ std::make_shared<Asset>(Asset{ m_tube_up, t_tube_up_day }) });
    tube_up.transform = glm::translate(glm::scale(tube_up.transform, glm::vec3(1, 1, 1)), glm::vec3(10, 4.55f, -9));

    Model tube_dn = Model::FromAssetList({ std::make_shared<Asset>(Asset{ m_tube_dn, t_tube_dn_day }) });
    tube_dn.transform = glm::translate(glm::scale(tube_dn.transform, glm::vec3(1, 1, 1)), glm::vec3(10, -4.55f, -9));

    // tube pool
    std::deque<std::pair<Model, Model>> tubes =
    {
        std::make_pair<Model, Model>(Model(tube_up), Model(tube_dn)),
        std::make_pair<Model, Model>(Model(tube_up), Model(tube_dn)),
        std::make_pair<Model, Model>(Model(tube_up), Model(tube_dn)),
        std::make_pair<Model, Model>(Model(tube_up), Model(tube_dn)),
        std::make_pair<Model, Model>(Model(tube_up), Model(tube_dn)),
        std::make_pair<Model, Model>(Model(tube_up), Model(tube_dn)),
        std::make_pair<Model, Model>(Model(tube_up), Model(tube_dn))
    };

    // tube starting positions
    {
        for (auto iter = tubes.begin() + 1; iter != tubes.end(); ++iter)
        {
            iter->first.transform[3].x = std::prev(iter)->first.transform[3].x + 4.f;
            iter->second.transform[3].x = std::prev(iter)->second.transform[3].x + 4.f;

            const GLfloat offset = static_cast<GLfloat>((rand() % 100) - 50) / 25.f;

            iter->first.transform[3].y = offset + 4.55f;
            iter->second.transform[3].y = offset - 4.55f;
        }
    }

    Camera camera(glm::vec3(0, 0, 0));
    GLuint score = 0;
    bool started = false;
    double old_time = glfwGetTime();
    double anim_interval = 0.1;

    // game loop
    {
        program.enable();
        while (window.isOpen())
        {
            glfwPollEvents();

            // bird animation
            const double new_time = glfwGetTime();
            if (new_time - old_time > anim_interval && !bird.crashed)
            {
                old_time = new_time;

                if (bird.model.assets.front()->texture == t_bird_1)
                { bird.model.assets.front()->texture = t_bird_2; }
                else if (bird.model.assets.front()->texture == t_bird_2)
                { bird.model.assets.front()->texture = t_bird_3; }
                else if (bird.model.assets.front()->texture == t_bird_3)
                { bird.model.assets.front()->texture = t_bird_1; }
            }

            if (key_pressed[GLFW_KEY_F])
            {
                started = true;
                anim_interval = 0.05;
            }

            // input processing
            {
                if (key_pressed[GLFW_KEY_9])
                {
                    backg.assets.front()->texture = t_backg_day;
                    tube_up.assets.front()->texture = t_tube_up_day;
                    tube_dn.assets.front()->texture = t_tube_dn_day;
                    ground.assets.front()->texture = t_ground_day;
                }

                if (key_pressed[GLFW_KEY_0])
                {
                    backg.assets.front()->texture = t_backg_ngt;
                    tube_up.assets.front()->texture = t_tube_up_ngt;
                    tube_dn.assets.front()->texture = t_tube_dn_ngt;
                    ground.assets.front()->texture = t_ground_ngt;
                }

                if (key_pressed[GLFW_KEY_1])
                { glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); }
                if (key_pressed[GLFW_KEY_2])
                { glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); }

                if (key_pressed[GLFW_KEY_W])
                { camera.move(CameraMoveDirection::Forward, 0.1f); }
                if (key_pressed[GLFW_KEY_S])
                { camera.move(CameraMoveDirection::Backward, 0.1f); }
                if (key_pressed[GLFW_KEY_A])
                { camera.move(CameraMoveDirection::Left, 0.1f); }
                if (key_pressed[GLFW_KEY_D])
                { camera.move(CameraMoveDirection::Right, 0.1f); }
                if (key_pressed[GLFW_KEY_SPACE])
                { camera.move(CameraMoveDirection::Up, 0.1f); }
                if (key_pressed[GLFW_KEY_LEFT_SHIFT])
                { camera.move(CameraMoveDirection::Down, 0.1f); }
                if (key_pressed[GLFW_KEY_Q])
                { camera.rotate(CameraRotationDirection::Roll, -5.f); }
                if (key_pressed[GLFW_KEY_E])
                { camera.rotate(CameraRotationDirection::Roll, 5.f); }
                if (key_pressed[GLFW_KEY_UP])
                { camera.rotate(CameraRotationDirection::Pitch, 5.f); }
                if (key_pressed[GLFW_KEY_DOWN])
                { camera.rotate(CameraRotationDirection::Pitch, -5.f); }
                if (key_pressed[GLFW_KEY_LEFT])
                { camera.rotate(CameraRotationDirection::Yaw, -5.f); }
                if (key_pressed[GLFW_KEY_RIGHT])
                { camera.rotate(CameraRotationDirection::Yaw, 5.f); }
            }

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            const GLfloat aspect_ratio = static_cast<GLfloat>(window.getWidth()) / static_cast<GLfloat>(window.getHeight());
            const glm::mat4 proj_view = glm::perspective(glm::radians(60.0f), aspect_ratio, 0.1f, 100.0f) * camera.getView();

            // moving
            if (started && !bird.crashed)
            {
                bird.update();

                if (!bird.tube_crashed)
                {
                    ground.transform[3].x -= .1f;
                    if (ground.transform[3].x <= -20.f)
                    {
                        ground.transform[3].x = 0;
                    }

                    backg.transform[3].x -= .01f;
                    if (backg.transform[3].x <= -15.f)
                    {
                        backg.transform[3].x = 0;
                    }

                    for (auto& tube : tubes)
                    {
                        bool potential_score = false;
                        if (bird.model.transform[3].x < tube.first.transform[3].x)
                        {
                            potential_score = true;
                        }

                        tube.first.transform[3].x -= .1f;
                        tube.second.transform[3].x -= .1f;

                        if (glm::abs(tube.first.transform[3].x - bird.model.transform[3].x) <= 0.8f &&
                            ((tube.first.transform[3].y - bird.model.transform[3].y <= 2.7f) ||
                            (bird.model.transform[3].y - tube.second.transform[3].y <= 4.8f)))
                        {
                            bird.tube_crashed = true;
                        }

                        if (potential_score && bird.model.transform[3].x >= tube.first.transform[3].x)
                        {
                            // TODO: display score
                            score += 1;
                            std::cout << "Score = " << score << std::endl;
                        }
                    }

                    if (tubes.front().first.transform[3].x <= -15.f)
                    {
                        tubes.front().first.transform[3].x = tubes.back().first.transform[3].x + 4.f;
                        tubes.front().second.transform[3].x = tubes.back().second.transform[3].x + 4.f;

                        tubes.push_back(tubes.front());
                        tubes.pop_front();

                        const GLfloat offset = static_cast<GLfloat>((rand() % 100) - 50) / 25.f;

                        tubes.back().first.transform[3].y = offset + 4.55f;
                        tubes.back().second.transform[3].y = offset - 4.55f;
                    }
                }
            }

            // drawing
            {
                program.setUniform("uMVP", proj_view * backg.transform); backg.draw();
                program.setUniform("uMVP", proj_view * ground.transform); ground.draw();
                program.setUniform("uMVP", proj_view * bird.model.transform); bird.model.draw();

                for (const auto& tube : tubes)
                {
                    program.setUniform("uMVP", proj_view * tube.first.transform); tube.first.draw();
                    program.setUniform("uMVP", proj_view * tube.second.transform); tube.second.draw();
                }
            }

            glfwPollEvents();
            window.update();
        }
        program.disable();
    }

    glfwTerminate();
    return 0;
}
