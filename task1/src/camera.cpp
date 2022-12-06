#include "camera.hpp"

glm::mat4 Camera::CalculateViewMatrix() const
{
    return glm::transpose(glm::toMat4(glm::quat(rotation))) * glm::translate(glm::identity<glm::mat4>(), -position);
}

glm::mat4 Camera::CalculateProjectionMatrix() const
{
  return glm::perspective(glm::radians(fov), aspect_ratio, near, far);
}