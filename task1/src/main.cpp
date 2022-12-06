#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include <iostream>
#include <chrono>

#include "shader.hpp"
#include "camera.hpp"
#include "mesh.hpp"

static const Vertex FIRST_TRIANGLE_VERTICES[3] = {
    {{0, -0.75, 0}, {0.5, 0, 0.5, 0.5}},
    {{0.5, 0.5, 0}, {1, 0, 0, 0.5}},
    {{-0.5, 0.5, 0}, {1, 0, 0, 0.5}},
};

static const Vertex SECOND_TRIANGLE_VERTICES[3] = {
    {{0, -1, 0}, {0.5, 0, 0.5, 0.5}},
    {{1, 1, 0}, {0, 0, 1, 0.5}},
    {{-1, 1, 0}, {0, 0, 1, 0.5}},
};

static const uint32_t TRIANGLE_INDICES[] = {
    0, 1, 2
};

GLFWwindow* g_Window = nullptr;
Camera g_Camera;

void init()
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize glfw!\n";
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, 1);
#endif

    g_Window = glfwCreateWindow(1280, 720, "Task1", nullptr, nullptr);
    assert(g_Window && "Can't create a window");

    glfwMakeContextCurrent(g_Window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD\n";
    }
}

int main()
{
    init();

    g_Camera.aspect_ratio = 1280.0f / 720.0f;
    g_Camera.position = {5, 0, 0};
    g_Camera.rotation = {0, 0, 0};

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // uint32_t first_shader  = CreateShader("assets/vertex_shader.vert", "assets/fragment_shader.frag");
    // uint32_t second_shader = CreateShader("assets/vertex_shader.vert", "assets/fragment_shader.frag");

    uint32_t shader = CreateShader("assets/vertex_shader.vert", "assets/fragment_shader.frag");
    uint32_t sphere_shader = CreateShader("assets/sphere.vert", "assets/sphere.frag");

    Mesh first_triangle{};
    first_triangle.rotation = {glm::radians(135.0f), 0, 0};
    first_triangle.Load(FIRST_TRIANGLE_VERTICES, 3, TRIANGLE_INDICES, 3);

    Mesh second_triangle{};
    second_triangle.rotation = {glm::radians(45.0f), 0, 0};
    second_triangle.Load(SECOND_TRIANGLE_VERTICES, 3, TRIANGLE_INDICES, 3);

    Mesh torus       = CreateTorusMesh(2, 0.5, 256, 1024);
    torus.position.x = -5;
    torus.rotation   = {glm::radians(45.0f), 0, 0};
    torus.scale      = 1;

    Mesh octahedron       = CreateOctahedronMesh(4);
    octahedron.position.x = -5;
    octahedron.scale      = 1;

    /* Color attachment */
    // uint32_t color_attachment = 0;
    // glGenTextures(1, &color_attachment);
    // glBindTexture(GL_TEXTURE_2D, color_attachment);

    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // glTexImage2D(GL_TEXTURE_2D, /*level=*/0, GL_RGBA8, 1280, 720, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    // glGenerateMipmap(GL_TEXTURE_2D);

    /* Depth attachment */
    // uint32_t depth_attachment = 0;
    // glGenTextures(1, &depth_attachment);
    // glBindTexture(GL_TEXTURE_2D, depth_attachment);

    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // glTexImage2D(GL_TEXTURE_2D, /*level=*/0, GL_R32F, 1280, 720, 0, GL_R32F, GL_UNSIGNED_INT, nullptr);
    // glGenerateMipmap(GL_TEXTURE_2D);

    /* Framebuffer */
    // uint32_t framebuffer = 0;
    // glGenFramebuffers(1, &framebuffer);
    // glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    // glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color_attachment, 0);
    // glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, depth_attachment, 0);

    auto start_time = std::chrono::steady_clock::now();

    while (!glfwWindowShouldClose(g_Window))
    {
        auto end_time = std::chrono::steady_clock::now();
        float time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count() / 1e6;
        constexpr float ROTATION_SPEED = 0.6f;
        constexpr float ZOOM_SPEED     = 0.75f;

        glClearColor(0, 0, 0, 0.5);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        g_Camera.position.x = (1 + 0.3 * sinf(ZOOM_SPEED * time)) * 12.5 * cosf(ROTATION_SPEED * time);
        g_Camera.position.z = -(1 + 0.3 * sinf(ZOOM_SPEED * time)) * 12.5 * sinf(ROTATION_SPEED * time);
        g_Camera.rotation.y = glm::radians(90.0f) + ROTATION_SPEED * time;

        glm::mat4 view_matrix = g_Camera.CalculateViewMatrix();
        glm::mat4 proj_matrix = g_Camera.CalculateProjectionMatrix();

        glUseProgram(shader);

        glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, false, glm::value_ptr(view_matrix));
        glUniformMatrix4fv(glGetUniformLocation(shader, "proj"), 1, false, glm::value_ptr(proj_matrix));

        first_triangle.Bind();
        first_triangle.LoadModelUniform(shader);
        glDrawElements(GL_TRIANGLES, first_triangle.index_count, GL_UNSIGNED_INT, nullptr);
        first_triangle.Unbind();

        second_triangle.Bind();
        second_triangle.LoadModelUniform(shader);
        glDrawElements(GL_TRIANGLES, second_triangle.index_count, GL_UNSIGNED_INT, nullptr);
        second_triangle.Unbind();

        torus.Bind();
        torus.LoadModelUniform(shader);
        glDrawElements(GL_TRIANGLES, torus.index_count, GL_UNSIGNED_INT, nullptr);
        torus.Unbind();

        glUseProgram(sphere_shader);

        glUniformMatrix4fv(glGetUniformLocation(sphere_shader, "view"), 1, false, glm::value_ptr(view_matrix));
        glUniformMatrix4fv(glGetUniformLocation(sphere_shader, "proj"), 1, false, glm::value_ptr(proj_matrix));
        glUniform1f(glGetUniformLocation(sphere_shader, "time"), time);

        octahedron.Bind();
        octahedron.LoadModelUniform(sphere_shader);
        glDrawElements(GL_TRIANGLES, octahedron.index_count, GL_UNSIGNED_INT, nullptr);
        octahedron.Unbind();

        
        // glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        // glUseProgram(first_shader);

        // glDisable(GL_DEPTH_TEST);
        // glDisable(GL_BLEND);
        // first_triangle.Bind();
        // first_triangle.LoadModelUniform(first_shader);
        // glUniformMatrix4fv(glGetUniformLocation(first_shader, "view"), 1, false, glm::value_ptr(view_matrix));
        // glUniformMatrix4fv(glGetUniformLocation(first_shader, "proj"), 1, false, glm::value_ptr(proj_matrix));
        // glDrawElements(GL_TRIANGLES, first_triangle.index_count, GL_UNSIGNED_INT, nullptr);
        // first_triangle.Unbind();

        // glBindFramebuffer(GL_FRAMEBUFFER, 0);
        // glUseProgram(second_shader);

        // glActiveTexture(GL_TEXTURE0);
        // glBindTexture(GL_TEXTURE_2D, color_attachment);
        // // glActiveTexture(GL_TEXTURE1);
        // // glBindTexture(GL_TEXTURE_2D, depth_attachment);

        // glUniform1i(glGetUniformLocation(second_shader, "color_texture"), 0);
        // // glUniform1i(glGetUniformLocation(second_shader, "depth_texture"), 1);

        // // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        // second_triangle.Bind();
        // second_triangle.LoadModelUniform(second_shader);
        // glUniformMatrix4fv(glGetUniformLocation(second_shader, "view"), 1, false, glm::value_ptr(view_matrix));
        // glUniformMatrix4fv(glGetUniformLocation(second_shader, "proj"), 1, false, glm::value_ptr(proj_matrix));
        // glDrawElements(GL_TRIANGLES, second_triangle.index_count, GL_UNSIGNED_INT, nullptr);
        // second_triangle.Unbind();

        glGetError();

        glfwSwapBuffers(g_Window);
        glfwPollEvents();
    }

    first_triangle.Delete();

    glfwTerminate();

    return 0;
}