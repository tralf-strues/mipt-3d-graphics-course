#include "material.hpp"

Material::Material(std::shared_ptr<Shader> shader) : shader_(shader) {}

void Material::LoadUniformsToShader() {
  shader_->Bind();

  for (const auto& uniform_int : uniforms_int_) {
    shader_->LoadUniformInt(uniform_int.second, uniform_int.first.c_str());
  }

  for (const auto& uniform_float : uniforms_float_) {
    shader_->LoadUniformFloat(uniform_float.second, uniform_float.first.c_str());
  }

  for (const auto& uniform_float2 : uniforms_float2_) {
    shader_->LoadUniformFloat2(uniform_float2.second, uniform_float2.first.c_str());
  }

  for (const auto& uniform_float3 : uniforms_float3_) {
    shader_->LoadUniformFloat3(uniform_float3.second, uniform_float3.first.c_str());
  }

  for (const auto& uniform_float4 : uniforms_float4_) {
    shader_->LoadUniformFloat4(uniform_float4.second, uniform_float4.first.c_str());
  }

  for (const auto& uniform_mat4 : uniforms_mat4_) {
    shader_->LoadUniformMat4(uniform_mat4.second, uniform_mat4.first.c_str());
  }

  for (const auto& uniform_bool : uniforms_bool_) {
    shader_->LoadUniformBool(uniform_bool.second, uniform_bool.first.c_str());
  }

  uint32_t texture_slot = 0;
  for (const auto& [name, texture] : textures_) {
    texture->Bind(texture_slot);
    shader_->LoadUniformInt(texture_slot, name.c_str());
    ++texture_slot;
  }

//   texture_slot = 0;
//   for (const auto& [name, cube_map] : cube_maps_) {
//     cube_map->Bind(texture_slot);
//     shader_->LoadUniformInt(texture_slot, name);
//     ++texture_slot;
//   }
}

void Material::SetShader(std::shared_ptr<Shader> shader) { shader_ = shader; }
Shader* Material::GetShader() { return shader_.get(); }

void Material::AddTexture(std::shared_ptr<Texture> texture, const char* name) { textures_[name] = texture; }
// void Material::AddCubeMap(std::shared_ptr<CubeMap> cube_map, const std::string& name) { cube_maps_[name] = cube_map; }