#pragma once

#include "glad/glad.h"
#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <memory>

class Shader {
public:
    uint32_t id{0};

    bool   depth_enabled{true};
    GLenum depth_func{GL_LESS};

    bool   blend_enabled{true};
    GLenum blend_src_factor{GL_SRC_ALPHA};
    GLenum blend_dst_factor{GL_ONE_MINUS_SRC_ALPHA};

public:
    ~Shader();
    void Bind() const;
    void Unbind() const;

    void LoadUniformInt(int value, const char* name);
    void LoadUniformUInt(uint32_t value, const char* name);
    void LoadUniformFloat(float value, const char* name);
    void LoadUniformFloat2(const glm::vec2& value, const char* name);
    void LoadUniformFloat3(const glm::vec3& value, const char* name);
    void LoadUniformFloat4(const glm::vec4& value, const char* name);
    void LoadUniformMat4(const glm::mat4& value, const char* name);
    void LoadUniformBool(bool value, const char* name);
};

std::shared_ptr<Shader> CreateShader(const std::string& vertex_shader_filepath, const std::string& fragment_shader_filepath);