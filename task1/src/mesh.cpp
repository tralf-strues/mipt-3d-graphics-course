#include "mesh.hpp"

#include "glad/glad.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <array>
#include <iostream>
#include <vector>

void Mesh::Load(const Vertex* vertices, uint32_t vertex_count, const uint32_t* indices, uint32_t index_count)
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_count * sizeof(uint32_t), indices, GL_STATIC_DRAW);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertex_count * sizeof(Vertex), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*) offsetof(Vertex, position));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(Vertex), (const void*) offsetof(Vertex, color));

    this->index_count = index_count;

    Unbind();
}

void Mesh::Delete()
{
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ibo);
    glDeleteVertexArrays(1, &vao);
}

void Mesh::Bind()
{
    glBindVertexArray(vao);
}

void Mesh::Unbind()
{
    glBindVertexArray(0);
}

void Mesh::LoadModelUniform(uint32_t shader_id)
{
    glm::mat4 model = glm::translate(glm::identity<glm::mat4>(), position) * glm::scale(glm::identity<glm::mat4>(), glm::vec3(scale)) * glm::toMat4(glm::quat(rotation));
    glUniformMatrix4fv(glGetUniformLocation(shader_id, "model"), 1, false, glm::value_ptr(model));
}

Mesh CreateTorusMesh(float outer_radius, float inner_radius, uint32_t outer_samples, uint32_t inner_samples) {
    const float outer_angle_delta = 2 * M_PI / outer_samples;
    const float inner_angle_delta = 2 * M_PI / inner_samples;

    const glm::vec4 middle_color = glm::vec4(0.5, 0.0, 0.75, 1);
    const glm::vec4 top_color    = glm::vec4(0.6, 0.8, 0.5, 1);

    std::vector<Vertex> vertices;
    for (uint32_t cur_outer = 0; cur_outer < outer_samples + 2; ++cur_outer) {
        float outer_angle = cur_outer * outer_angle_delta;

        for (uint32_t cur_inner = 0; cur_inner < inner_samples + 2; ++cur_inner) {
            float inner_angle = cur_inner * inner_angle_delta;

            Vertex vertex{};
            vertex.position.x = cosf(outer_angle) * (outer_radius + inner_radius * cosf(inner_angle));
            vertex.position.y = inner_radius * sinf(inner_angle);
            vertex.position.z = sinf(outer_angle) * (outer_radius + inner_radius * cosf(inner_angle));

            float ratio = fmod(inner_angle + M_PI_2, M_PI_2) / M_PI_2;
            vertex.color = middle_color * ratio + top_color * (1 - ratio);
            vertex.color.a = 1.0f;

            vertices.emplace_back(std::move(vertex));
        }
    }

    std::vector<uint32_t> indices;
    for (uint32_t cur_outer = 0; cur_outer < outer_samples; ++cur_outer) {
        for (uint32_t cur_inner = 0; cur_inner < inner_samples; ++cur_inner) {
            uint32_t idx0 = cur_outer * inner_samples + cur_inner;
            uint32_t idx1 = cur_inner + 1 == inner_samples ? cur_outer * inner_samples : idx0 + 1;
            uint32_t idx2 = cur_outer + 1 == outer_samples ? (idx0 + inner_samples) % inner_samples : idx0 + inner_samples;
            uint32_t idx3 = cur_inner + 1 == inner_samples ? cur_outer * inner_samples : idx2 + 1;

            indices.push_back(idx3);
            indices.push_back(idx1);
            indices.push_back(idx0);

            indices.push_back(idx2);
            indices.push_back(idx3);
            indices.push_back(idx0);
        }
    }

    Mesh torus_mesh{};

    glGenVertexArrays(1, &torus_mesh.vao);
    glBindVertexArray(torus_mesh.vao);

    glGenBuffers(1, &torus_mesh.ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, torus_mesh.ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &torus_mesh.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, torus_mesh.vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*) offsetof(Vertex, position));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(Vertex), (const void*) offsetof(Vertex, color));

    torus_mesh.index_count = indices.size();

    glBindVertexArray(0);

    return torus_mesh;
}

void SubdivideTriangle(const std::array<glm::vec3, 3> &triangle_vertices,
                       const glm::vec4& color,
                       uint32_t subdivisions,
                       uint32_t first_index,
                       std::vector<Vertex>& vertices,
                       std::vector<uint32_t>& indices) {
    uint32_t side_points_count = (1 << subdivisions) + 1;

    for (uint32_t cur_points_count = side_points_count; cur_points_count > 0; --cur_points_count) {
        float cur_alpha = static_cast<float>(side_points_count - cur_points_count) / static_cast<float>(side_points_count - 1);

        glm::vec3 cur_left  = (1 - cur_alpha) * triangle_vertices[0] + cur_alpha * triangle_vertices[2];
        glm::vec3 cur_right = (1 - cur_alpha) * triangle_vertices[1] + cur_alpha * triangle_vertices[2];
        glm::vec3 cur_step  = cur_points_count > 1 ? (cur_right - cur_left) / static_cast<float>(cur_points_count - 1) : glm::vec3{0, 0, 0};

        for (uint32_t i = 0; i < cur_points_count; ++i) {
            Vertex vertex{};
            vertex.position = cur_left + static_cast<float>(i) * cur_step;
            vertex.color    = color;
            vertices.push_back(vertex);
        }
    }

    uint32_t total_points = 0;
    for (uint32_t cur_points_count = side_points_count; cur_points_count > 1; --cur_points_count) {
        for (uint32_t i = 0; i < cur_points_count - 1; ++i) {
            indices.push_back(first_index + i + total_points);
            indices.push_back(first_index + i + 1 + total_points);
            indices.push_back(first_index + i + total_points + cur_points_count);

            if (i + 2 < cur_points_count) {
                indices.push_back(first_index + i + total_points + cur_points_count);
                indices.push_back(first_index + i + 1 + total_points);
                indices.push_back(first_index + i + 1 + total_points + cur_points_count);
            }
        }

        total_points += cur_points_count;
    }
}

Mesh CreateOctahedronMesh(uint32_t subdivisions) {
    std::array<glm::vec3, 3> triangle0 = {glm::vec3{1, 0, 0},  glm::vec3{0, 0, 1},  glm::vec3{0, 1, 0}};
    std::array<glm::vec3, 3> triangle1 = {glm::vec3{0, 0, 1},  glm::vec3{-1, 0, 0}, glm::vec3{0, 1, 0}};
    std::array<glm::vec3, 3> triangle2 = {glm::vec3{-1, 0, 0}, glm::vec3{0, 0, -1}, glm::vec3{0, 1, 0}};
    std::array<glm::vec3, 3> triangle3 = {glm::vec3{0, 0, -1}, glm::vec3{1, 0, 0},  glm::vec3{0, 1, 0}};

    std::array<glm::vec3, 3> triangle4 = {glm::vec3{0, 0, 1},  glm::vec3{1, 0, 0},  glm::vec3{0, -1, 0}};
    std::array<glm::vec3, 3> triangle5 = {glm::vec3{-1, 0, 0}, glm::vec3{0, 0, 1},  glm::vec3{0, -1, 0}};
    std::array<glm::vec3, 3> triangle6 = {glm::vec3{0, 0, -1}, glm::vec3{-1, 0, 0}, glm::vec3{0, -1, 0}};
    std::array<glm::vec3, 3> triangle7 = {glm::vec3{1, 0, 0},  glm::vec3{0, 0, -1}, glm::vec3{0, -1, 0}};

    std::vector<Vertex>   vertices;
    std::vector<uint32_t> indices;

    SubdivideTriangle(triangle0, glm::vec4{0.75, 0, 0, 1}, subdivisions, vertices.size(), vertices, indices);
    SubdivideTriangle(triangle1, glm::vec4{0, 0.75, 0, 1}, subdivisions, vertices.size(), vertices, indices);
    SubdivideTriangle(triangle2, glm::vec4{0, 0, 0.75, 1}, subdivisions, vertices.size(), vertices, indices);
    SubdivideTriangle(triangle3, glm::vec4{0.75, 0.75, 0, 1}, subdivisions, vertices.size(), vertices, indices);

    SubdivideTriangle(triangle4, glm::vec4{0.75, 0, 0, 1}, subdivisions, vertices.size(), vertices, indices);
    SubdivideTriangle(triangle5, glm::vec4{0, 0.75, 0, 1}, subdivisions, vertices.size(), vertices, indices);
    SubdivideTriangle(triangle6, glm::vec4{0, 0, 0.75, 1}, subdivisions, vertices.size(), vertices, indices);
    SubdivideTriangle(triangle7, glm::vec4{0.75, 0.75, 0, 1}, subdivisions, vertices.size(), vertices, indices);

    Mesh octahedron_mesh{};

    glGenVertexArrays(1, &octahedron_mesh.vao);
    glBindVertexArray(octahedron_mesh.vao);

    glGenBuffers(1, &octahedron_mesh.ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, octahedron_mesh.ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &octahedron_mesh.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, octahedron_mesh.vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*) offsetof(Vertex, position));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(Vertex), (const void*) offsetof(Vertex, color));

    octahedron_mesh.index_count = indices.size();

    glBindVertexArray(0);

    return octahedron_mesh;
}