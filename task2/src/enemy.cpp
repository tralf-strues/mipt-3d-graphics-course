#include "enemy.hpp"
#include "player.hpp"
#include "random.hpp"

void Enemy::OnUpdate(GameWorld* world) {
    Player* player = world->GetMainPlayer();

    glm::vec3 to_player = glm::normalize(player->position - position);

    if (position.x <= player->position.x) {
        rotation.y = M_PI - acosf(glm::dot(to_player, glm::vec3{0, 0, -1}));
    } else {
        rotation.y = M_PI + acosf(glm::dot(to_player, glm::vec3{0, 0, -1}));
    }

    position += to_player * speed * world->DeltaTime();
}

void EnemySpawner::OnUpdate(GameWorld* world) {
    recharge_time_ -= world->DeltaTime();

    if (recharge_time_ <= 0) {
        glm::vec3 spawn_position;
        spawn_position.x = Random::RandomRangeFloat(spawn_volume_first.x, spawn_volume_second.x);
        spawn_position.y = Random::RandomRangeFloat(spawn_volume_first.y, spawn_volume_second.y);
        spawn_position.z = Random::RandomRangeFloat(spawn_volume_first.z, spawn_volume_second.z);

        Enemy* enemy      = world->Instantiate<Enemy>(spawn_position, spawn_mesh_);
        enemy->scale      = enemy_scale;
        enemy->collidable = true;
        enemy->aabb       = AABB{glm::vec3{-0.75, 0, -0.75}, glm::vec3{0.75, 1.5, 0.75}};

        recharge_time_ = Random::RandomRangeFloat(spawn_rate_first, spawn_rate_second);
    }
}