#pragma once

#include "mesh_object.hpp"
#include "mesh.hpp"

class Enemy : public MeshObject {
public:
    Enemy(std::shared_ptr<Mesh> mesh) : MeshObject(mesh) {}
    virtual ~Enemy() override = default;

    virtual void OnUpdate(GameWorld* world) override;

public:
    float speed{1.2};
};

class EnemySpawner : public GameObject {
public:
    EnemySpawner(const glm::vec3 &spawn_volume_first,
                 const glm::vec3 &spawn_volume_second,
                 float spawn_rate_first,
                 float spawn_rate_second,
                 float enemy_scale)
                 : spawn_volume_first(spawn_volume_first),
                   spawn_volume_second(spawn_volume_second),
                   spawn_rate_first(spawn_rate_first),
                   spawn_rate_second(spawn_rate_second),
                   enemy_scale(enemy_scale) {}

    virtual ~EnemySpawner() override = default;

    virtual void OnUpdate(GameWorld* world) override;

    void SetMesh(std::shared_ptr<Mesh> mesh) { spawn_mesh_ = mesh; }

public:
    glm::vec3 spawn_volume_first;
    glm::vec3 spawn_volume_second;
    float     spawn_rate_first;
    float     spawn_rate_second;
    float     enemy_scale{1};

private:
    float                 recharge_time_{0};
    std::shared_ptr<Mesh> spawn_mesh_;
};