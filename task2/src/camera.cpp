#include "camera.hpp"

glm::mat4 Camera::CalculateViewMatrix() const
{
    return glm::transpose(glm::toMat4(glm::quat(rotation))) * glm::translate(glm::identity<glm::mat4>(), -position);
}

glm::mat4 Camera::CalculateProjectionMatrix() const
{
  return glm::perspective(glm::radians(fov), aspect_ratio, near, far);
}

glm::vec3 Camera::Forward() const {
  constexpr glm::vec3 kDefaultForward = glm::vec3{0, 0, -1};
  return glm::normalize(glm::vec3{glm::toMat4(glm::quat(rotation)) * glm::vec4{kDefaultForward, 1}});
}

glm::vec3 Camera::Right() const {
  constexpr glm::vec3 kDefaultRight = glm::vec3{1, 0, 0};
  return glm::normalize(glm::vec3{glm::toMat4(glm::quat(rotation)) * glm::vec4{kDefaultRight, 1}});
}

glm::vec3 Camera::Up() const {
  constexpr glm::vec3 kDefaultUp = glm::vec3{0, 1, 0};
  return glm::normalize(glm::vec3{glm::toMat4(glm::quat(rotation)) * glm::vec4{kDefaultUp, 1}});
}
