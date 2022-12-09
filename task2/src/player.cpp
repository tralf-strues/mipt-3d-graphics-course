#include "player.hpp"
#include "input.hpp"

#include <iostream>

void Player::OnUpdate(GameWorld* world) {
    cur_recharge_time_ -= world->DeltaTime();

    glm::vec3 delta_pos{0};

    if (Keyboard::Pressed(GLFW_KEY_W)) {
        delta_pos += speed * camera.Forward() * world->DeltaTime();
    }

    if (Keyboard::Pressed(GLFW_KEY_S)) {
        delta_pos -= speed * camera.Forward() * world->DeltaTime();
    }

    if (Keyboard::Pressed(GLFW_KEY_A)) {
        delta_pos -= speed * camera.Right() * world->DeltaTime();
    }

    if (Keyboard::Pressed(GLFW_KEY_D)) {
        delta_pos += speed * camera.Right() * world->DeltaTime();
    }

    delta_pos.y = 0;
    position += delta_pos;

    velocity.y -= 9.8f * world->DeltaTime();
    position += velocity * world->DeltaTime();

    if (position.y <= floor_level) {
        position.y = floor_level;
        velocity.y = 0;
    }

    camera.position = position + glm::vec3{0, kPlayerCameraHeight, 0};
}

void Player::OnKeyPressed(GameWorld* world, GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (Keyboard::Pressed(GLFW_KEY_SPACE) && position.y == floor_level) {
        velocity += glm::vec3{0, 1, 0} * jump_strength;
    }
}

void Player::OnMouseMoved(GameWorld* world, GLFWwindow* window, float dx, float dy) {
    camera.rotation.x += 0.001f * dy;
    camera.rotation.y += 0.001f * dx;
}

void Player::OnMousePressed(GameWorld* world, GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && cur_recharge_time_ <= 0) {
        glm::vec3 forward    = camera.Forward();
        glm::vec3 fire_point = camera.position + forward * 2.0f;

        Bullet* bullet   = world->Instantiate<Bullet>(fire_point, bullet_mesh);
        bullet->scale    = 0.1f;
        bullet->velocity = forward * bullet_speed;
        bullet->lifespan = bullet_lifespan;
        
        bullet->collidable = true;
        bullet->aabb       = AABB{glm::vec3{-0.05, -0.05, -0.05}, glm::vec3{0.05, 0.05, 0.05}};

        cur_recharge_time_ = recharge_time;
    }
}

void Bullet::OnStart(GameWorld* world) {
    time_left_ = lifespan;
}

void Bullet::OnUpdate(GameWorld* world) {
    time_left_ -= world->DeltaTime();
    if (time_left_ <= 0) {
        world->SubmitDeferDelete(this);
    }

    position += velocity * world->DeltaTime();
}

void Bullet::OnCollision(GameWorld* world, GameObject* other) {
    world->SubmitDeferDelete(this);
    world->SubmitDeferDelete(other);
}