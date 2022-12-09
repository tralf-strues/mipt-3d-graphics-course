#pragma once

#include "material.hpp"

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec4 color;
    glm::vec2 uv;
};

struct Mesh
{
public:
    uint32_t vao{0};
    uint32_t ibo{0};
    uint32_t vbo{0};
    uint32_t index_count{0};

    std::shared_ptr<Material> material;

public:
    void Create(const Vertex* vertices, uint32_t vertex_count, const uint32_t* indices, uint32_t index_count);
    void Delete();

    void Draw();

    void Bind();
    void Unbind();
};

std::shared_ptr<Mesh> ImportMesh(const char* filepath);
std::shared_ptr<Mesh> CreateTorusMesh(float main_radius, float slice_radius, uint32_t outer_samples, uint32_t inner_samples);
std::shared_ptr<Mesh> CreateOctahedronMesh(uint32_t subdivision);