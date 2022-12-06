#include "mesh.hpp"

#include "glad/glad.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

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
    glm::mat4 model = glm::translate(glm::identity<glm::mat4>(), position) * glm::toMat4(glm::quat(rotation));
    glUniformMatrix4fv(glGetUniformLocation(shader_id, "model"), 1, false, glm::value_ptr(model));
}
