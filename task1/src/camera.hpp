#pragma once

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Camera
{
  float fov = 45.0f;
  float near = 0.5f;
  float far = 1000.0f;
  float aspect_ratio = 0.0f;

  glm::vec3 position;
  glm::vec3 rotation;

  glm::mat4 CalculateViewMatrix() const;
  glm::mat4 CalculateProjectionMatrix() const;
};