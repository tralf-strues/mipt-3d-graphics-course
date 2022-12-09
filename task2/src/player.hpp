#pragma once

#include "camera.hpp"
#include "game_object.hpp"
#include "mesh_object.hpp"

constexpr float kPlayerCameraHeight = 1;

class Player : public GameObject {
public:
    Player() = default;
    virtual ~Player() override = default;

    virtual void OnUpdate(GameWorld* world) override;
    
    virtual void OnKeyPressed(GameWorld* world, GLFWwindow* window, int key, int scancode, int action, int mods) override;
    virtual void OnMouseMoved(GameWorld* world, GLFWwindow* window, float dx, float dy) override;
    virtual void OnMousePressed(GameWorld* world, GLFWwindow* window, int button, int action, int mods) override;

public:
    Camera                camera{};

    float                 jump_strength{1};
    float                 speed{1};
    glm::vec3             velocity{0};
    float                 floor_level{0};

    float                 recharge_time{0};
    std::shared_ptr<Mesh> bullet_mesh{nullptr};
    float                 bullet_speed{0};
    float                 bullet_lifespan{1};

private:
    float                 cur_recharge_time_{0};
};

class Bullet : public MeshObject {
public:
    Bullet(std::shared_ptr<Mesh> mesh) : MeshObject(mesh) {}
    virtual ~Bullet() override = default;

    virtual void OnStart(GameWorld* world) override;
    virtual void OnUpdate(GameWorld* world) override;

    virtual void OnCollision(GameWorld* world, GameObject* other) override;

public:
    glm::vec3 velocity{0, 0, 0};
    float     lifespan{1};

private:
    float     time_left_{0};
};