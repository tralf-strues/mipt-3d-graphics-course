#pragma once

#include "glad/glad.h"
#include <string>

uint32_t CreateShader(const std::string& vertex_shader_filepath, const std::string& fragment_shader_filepath);