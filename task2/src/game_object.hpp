#pragma once

#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glad/glad.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <chrono>
#include <vector>
#include <set>

struct RenderView {
    glm::mat4 view_matrix;
    glm::mat4 proj_matrix;
    float     time;
};

struct AABB {
    glm::vec3 min_point{0};
    glm::vec3 max_point{0};

    bool IntersectsWith(const AABB& other) const {
        return min_point.x <= other.max_point.x &&
               max_point.x >= other.min_point.x &&
               min_point.y <= other.max_point.y &&
               max_point.y >= other.min_point.y &&
               min_point.z <= other.max_point.z &&
               max_point.z >= other.min_point.z;
    }
};

class GameWorld;
class Player;

class GameObject {
public:
    virtual ~GameObject() = default;

    virtual void OnStart(GameWorld*) {}
    virtual void OnUpdate(GameWorld*) {}
    virtual void OnRender(GameWorld*, const RenderView&) {}

    virtual void OnCollision(GameWorld* world, GameObject* other) {}
    
    virtual void OnKeyPressed(GameWorld* world, GLFWwindow* window, int key, int scancode, int action, int mods) {}
    virtual void OnMouseMoved(GameWorld* world, GLFWwindow* window, float dx, float dy) {}
    virtual void OnMousePressed(GameWorld* world, GLFWwindow* window, int button, int action, int mods) {}

    glm::mat4 GetModelMatrix() {
        return glm::translate(glm::identity<glm::mat4>(), position) *
               glm::scale(glm::identity<glm::mat4>(), glm::vec3(scale)) *
               glm::toMat4(glm::quat(rotation));
    }

    glm::vec3 Forward() const {
        constexpr glm::vec3 kDefaultForward = glm::vec3{0, 0, -1};
        return glm::normalize(glm::vec3{glm::toMat4(glm::quat(rotation)) * glm::vec4{kDefaultForward, 1}});
    }

    glm::vec3 Right() const {
        constexpr glm::vec3 kDefaultRight = glm::vec3{1, 0, 0};
        return glm::normalize(glm::vec3{glm::toMat4(glm::quat(rotation)) * glm::vec4{kDefaultRight, 1}});
    }

    glm::vec3 Up() const {
        constexpr glm::vec3 kDefaultUp = glm::vec3{0, 1, 0};
        return glm::normalize(glm::vec3{glm::toMat4(glm::quat(rotation)) * glm::vec4{kDefaultUp, 1}});
    }

public:
    glm::vec3 position{0, 0, 0};
    glm::vec3 rotation{0, 0, 0};
    float     scale{1};

    bool      collidable{false};
    AABB      aabb{};
};

class GameWorld {
public:
    template<typename T, typename... Args>
    T* Instantiate(const glm::vec3& position, Args&&... args) {
        static_assert(std::is_base_of<GameObject, T>());
        T* game_object = new T(std::forward<Args>(args)...);
        game_objects_.insert(game_object);

        game_object->position = position;

        game_object->OnStart(this);

        return game_object;
    }

    void SubmitDeferDelete(GameObject* game_object) {
        delete_queue_.push_back(game_object);
    }

    void DeleteDeferred() {
        for (auto& game_object : delete_queue_) {
            if (game_objects_.find(game_object) != game_objects_.end()) {
                game_objects_.erase(game_object);
                delete game_object;
            }
        }

        delete_queue_.clear();
    }

    void RestartTime() {
        start_time_     = std::chrono::steady_clock::now();
        cur_time_       = 0;
        cur_delta_time_ = 0;
    }

    void UpdateTime() {
        auto time_point = std::chrono::steady_clock::now();
        float new_time = std::chrono::duration_cast<std::chrono::microseconds>(time_point - start_time_).count() / 1e6;

        cur_delta_time_ = new_time - cur_time_;
        cur_time_ = new_time;
    }

    float Time() const { return cur_time_; }
    float DeltaTime() const { return cur_delta_time_; }

    Player* GetMainPlayer() const { return main_player_; }
    void SetMainPlayer(Player* player) { main_player_ = player; }

    void UpdateAll() {
        for (auto& game_object : game_objects_) {
            game_object->OnUpdate(this);
        }
    }

    void CollideAll() {
        for (auto it1 = game_objects_.begin(); it1 != game_objects_.end(); ++it1) {
            GameObject* first = *it1;
            if (!first->collidable) { continue; }

            for (auto it2 = it1; it2 != game_objects_.end(); ++it2) {
                GameObject* second = *it2;
                if (!second->collidable || first == second) { continue; }

                AABB first_aabb = first->aabb;
                first_aabb.min_point += first->position;
                first_aabb.max_point += first->position;

                AABB second_aabb = second->aabb;
                second_aabb.min_point += second->position;
                second_aabb.max_point += second->position;

                if (first_aabb.IntersectsWith(second_aabb)) {
                    first->OnCollision(this, second);
                    second->OnCollision(this, first);
                }
            }
        }
    }
    
    void RenderAll(const RenderView& render_view) {
        for (auto& game_object : game_objects_) {
            game_object->OnRender(this, render_view);
        }
    }

    void OnKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods) {
        for (auto& game_object : game_objects_) {
            game_object->OnKeyPressed(this, window, key, scancode, action, mods);
        }
    }

    void OnMouseMoved(GLFWwindow* window, float dx, float dy) {
        for (auto& game_object : game_objects_) {
            game_object->OnMouseMoved(this, window, dx, dy);
        }
    }

    void OnMousePressed(GLFWwindow* window, int button, int action, int mods) {
        for (auto& game_object : game_objects_) {
            game_object->OnMousePressed(this, window, button, action, mods);
        }
    }

private:
    std::set<GameObject*> game_objects_;
    std::vector<GameObject*> delete_queue_;

    Player* main_player_{nullptr};

    std::chrono::time_point<std::chrono::steady_clock> start_time_;
    float cur_time_{0};
    float cur_delta_time_{0};
};