#include "shader.hpp"
#include <iostream>
#include <fstream>

Shader::~Shader() {
    glDeleteProgram(id);
}

void Shader::Bind() const {
    glUseProgram(id);
}

void Shader::Unbind() const {
    glUseProgram(0);
}

void Shader::LoadUniformInt(int value, const char* name) {
  Bind();
  glUniform1i(glGetUniformLocation(id, name), value);
}

void Shader::LoadUniformUInt(uint32_t value, const char* name) {
  Bind();
  glUniform1ui(glGetUniformLocation(id, name), value);
}

void Shader::LoadUniformFloat(float value, const char* name) {
  Bind();
  glUniform1f(glGetUniformLocation(id, name), value);
}

void Shader::LoadUniformFloat2(const glm::vec2& value, const char* name) {
  Bind();
  glUniform2f(glGetUniformLocation(id, name), value.x, value.y);
}

void Shader::LoadUniformFloat3(const glm::vec3& value, const char* name) {
  Bind();
  glUniform3f(glGetUniformLocation(id, name), value.x, value.y, value.z);
}

void Shader::LoadUniformFloat4(const glm::vec4& value, const char* name) {
  Bind();
  glUniform4f(glGetUniformLocation(id, name), value.x, value.y, value.z, value.w);
}

void Shader::LoadUniformMat4(const glm::mat4& value, const char* name) {
  Bind();
  int location = glGetUniformLocation(id, name);
  glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::LoadUniformBool(bool value, const char* name) {
  Bind();
  glUniform1i(glGetUniformLocation(id, name), value);
}

static void ReadFile(const std::string& filepath, std::string* data)
{
    std::ifstream file(filepath, std::ios::ate);
    if (!file.is_open())
    {
        std::cerr << "File \"" << filepath << "\" is not found!\n";
        return;
    }

    uint64_t file_size = file.tellg();
    data->resize(file_size);

    file.seekg(0);
    file.read(data->data(), file_size);

    std::cout << "File size: " << file_size << "\n";
    std::cout << "Fragment shader:\n" << *data << "\n";

    file.close();
}

static uint32_t CompileShader(uint32_t type, const std::string &source)
{
    uint32_t id = glCreateShader(type);
    const char* c_source = source.c_str();

    glShaderSource(id, /*count=*/1, &c_source, /*length=*/nullptr);
    glCompileShader(id);

    int32_t result = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int32_t length = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

        char* message = (char*) alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);

        std::cerr << "Failed to compile shader of type " << type << ":\n\t" << message << "\n";

        glDeleteShader(id);
        return 0;
    }

    return id;
}

std::shared_ptr<Shader> CreateShader(const std::string& vertex_shader_filepath, const std::string& fragment_shader_filepath)
{
    std::string vertex_shader;
    std::string fragment_shader;

    ReadFile(vertex_shader_filepath, &vertex_shader);
    ReadFile(fragment_shader_filepath, &fragment_shader);

    uint32_t vs = CompileShader(GL_VERTEX_SHADER, vertex_shader);
    uint32_t fs = CompileShader(GL_FRAGMENT_SHADER, fragment_shader);

    uint32_t program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    std::shared_ptr<Shader> shader{std::make_shared<Shader>()};
    shader->id = program;

    return shader;
}