#pragma once

#include "shader.hpp"
#include "texture.hpp"

#include "glm/glm.hpp"
#include <map>
#include <memory>

class Material {
 public:
  Material() = default;
  Material(std::shared_ptr<Shader> shader);

  void LoadUniformsToShader();

  void SetShader(std::shared_ptr<Shader> shader);
  Shader* GetShader();

  void AddTexture(std::shared_ptr<Texture> texture, const char* name);

//   void AddCubeMap(std::shared_ptr<CubeMap> cube_map, const std::string& name);

  template <typename T>
  inline void SetUniform(const T& value, const std::string& name) {
    if      constexpr (std::is_same<T, int>())       { uniforms_int_   [name] = value; }
    else if constexpr (std::is_same<T, float>())     { uniforms_float_ [name] = value; }
    else if constexpr (std::is_same<T, glm::vec2>()) { uniforms_float2_[name] = value; }
    else if constexpr (std::is_same<T, glm::vec3>()) { uniforms_float3_[name] = value; }
    else if constexpr (std::is_same<T, glm::vec4>()) { uniforms_float4_[name] = value; }
    else if constexpr (std::is_same<T, glm::mat4>()) { uniforms_mat4_  [name] = value; }
    else if constexpr (std::is_same<T, bool>())      { uniforms_bool_  [name] = value; }
    else {
      static_assert(std::is_same<T, std::false_type>(), "Unsupported uniform data type in Material::SetUniform()");
    }
  }

 private:
  std::shared_ptr<Shader> shader_{nullptr};
  std::map<std::string, std::shared_ptr<Texture>> textures_;
//   std::map<std::string, std::shared_ptr<CubeMap>> cube_maps_;

  std::map<std::string, int>       uniforms_int_;
  std::map<std::string, float>     uniforms_float_;
  std::map<std::string, glm::vec2> uniforms_float2_;
  std::map<std::string, glm::vec3> uniforms_float3_;
  std::map<std::string, glm::vec4> uniforms_float4_;
  std::map<std::string, glm::mat4> uniforms_mat4_;
  std::map<std::string, bool>      uniforms_bool_;
};