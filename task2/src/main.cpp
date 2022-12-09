#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include <iostream>
#include <chrono>

#include "shader.hpp"
#include "camera.hpp"
#include "mesh.hpp"
#include "game_object.hpp"
#include "enemy.hpp"
#include "player.hpp"
#include "input.hpp"

constexpr uint32_t kWindowWidth   = 1280;
constexpr uint32_t kWindowHeight  = 720;
constexpr uint32_t kWindowCenterX = kWindowWidth / 2;
constexpr uint32_t kWindowCenterY = kWindowHeight / 2;

GLFWwindow* g_Window = nullptr;
GameWorld   g_GameWorld;

std::shared_ptr<Shader> basic_shader;

void GenFloor();
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void MouseMoveCallback(GLFWwindow* window, double new_x, double new_y);
void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

void init() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize glfw!\n";
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, 1);
#endif

    g_Window = glfwCreateWindow(kWindowWidth, kWindowHeight, "Task1", nullptr, nullptr);
    assert(g_Window && "Can't create a window");

    glfwMakeContextCurrent(g_Window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
    }
}

int main() {
    init();

    glfwSetInputMode(g_Window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glfwSetKeyCallback(g_Window, KeyCallback);
    glfwSetCursorPosCallback(g_Window, MouseMoveCallback);
    glfwSetMouseButtonCallback(g_Window, MouseButtonCallback);

    basic_shader = CreateShader("assets/shaders/basic.vert", "assets/shaders/basic.frag");

    g_GameWorld.RestartTime();

    GenFloor();

    std::shared_ptr<Mesh> enemy_mesh = ImportMesh("assets/meshes/monster.obj");
    enemy_mesh->material = std::make_shared<Material>(basic_shader);
    enemy_mesh->material->AddTexture(std::make_shared<Texture>("assets/texture/monster_albedo.jpg"), "albedo");

    std::shared_ptr<Mesh> bullet_mesh = ImportMesh("assets/meshes/bullet_sphere.fbx");
    bullet_mesh->material = std::make_shared<Material>(basic_shader);
    bullet_mesh->material->AddTexture(std::make_shared<Texture>("assets/texture/bullet_albedo.jpg"), "albedo");

    Player* player = g_GameWorld.Instantiate<Player>(glm::vec3{0, 0, 0});
    player->camera.aspect_ratio = static_cast<float>(kWindowWidth) / static_cast<float>(kWindowHeight);
    player->jump_strength       = 4.0f;
    player->speed               = 2.0f;
    player->recharge_time       = 0.3f;
    player->bullet_speed        = 50.0f;
    player->bullet_mesh         = bullet_mesh;
    player->bullet_lifespan     = 10.0f;
    g_GameWorld.SetMainPlayer(player);

    EnemySpawner* spawner = g_GameWorld.Instantiate<EnemySpawner>(glm::vec3{0, 0, 0}, glm::vec3{-30, 0, -30}, glm::vec3{30, 0, 30}, 0.5, 2, 0.005);
    spawner->SetMesh(enemy_mesh);

    while (!glfwWindowShouldClose(g_Window)) {
        g_GameWorld.UpdateTime();
        g_GameWorld.UpdateAll();
        g_GameWorld.CollideAll();

        glClearColor(0.1, 0.01, 0.1, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        RenderView render_view{player->camera.CalculateViewMatrix(),
                               player->camera.CalculateProjectionMatrix(),
                               g_GameWorld.Time()};

        g_GameWorld.RenderAll(render_view);
        g_GameWorld.DeleteDeferred();

        glGetError();

        glfwSwapBuffers(g_Window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

void GenFloor() {
    std::shared_ptr<Mesh> floor_mesh = ImportMesh("assets/meshes/floor.fbx");
    floor_mesh->material = std::make_shared<Material>(basic_shader);
    floor_mesh->material->AddTexture(std::make_shared<Texture>("assets/texture/floor_albedo.jpg"), "albedo");

    constexpr float kTileSize = 5;
    constexpr int32_t kTilesCount = 12;

    for (int32_t tile_x = 0; tile_x < kTilesCount; ++tile_x) {
        float cur_x = (-(kTilesCount / 2) + tile_x) * kTileSize;

        for (int32_t tile_z = 0; tile_z < kTilesCount; ++tile_z) {
            float cur_z = (-(kTilesCount / 2) + tile_z) * kTileSize;

            MeshObject* floor = g_GameWorld.Instantiate<MeshObject>(glm::vec3{cur_x, 0, cur_z}, floor_mesh);
            floor->scale = 0.1;
        }
    }
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        Keyboard::GetKeys()[key] = true;
    } else if (action == GLFW_RELEASE) {
        Keyboard::GetKeys()[key] = false;
    }

    g_GameWorld.OnKeyPressed(window, key, scancode, action, mods);
}

void MouseMoveCallback(GLFWwindow* window, double new_x, double new_y) {
    static bool skip = true;
    if (skip)
    {
        glfwSetCursorPos(window, kWindowCenterX, kWindowCenterY);
        skip = false;
        return;
    }

    float dx = static_cast<float>(kWindowCenterX) - new_x;
    float dy = static_cast<float>(kWindowCenterY) - new_y;

    g_GameWorld.OnMouseMoved(window, dx, dy);

    glfwSetCursorPos(window, kWindowCenterX, kWindowCenterY);
}

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    g_GameWorld.OnMousePressed(window, button, action, mods);
}