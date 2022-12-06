#pragma once

#include "glm/glm.hpp"

struct Vertex
{
    glm::vec3 position;
    glm::vec4 color;
};

struct Mesh
{
    uint32_t vao{0};
    uint32_t ibo{0};
    uint32_t vbo{0};
    uint32_t index_count{0};

    glm::vec3 position{0, 0, 0};
    glm::vec3 rotation{0, 0, 0};


    void Load(const Vertex* vertices, uint32_t vertex_count, const uint32_t* indices, uint32_t index_count);
    void Delete();

    void Bind();
    void Unbind();
    
    void LoadModelUniform(uint32_t shader_id);
};