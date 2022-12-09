#pragma once

#include <glad/glad.h>
#include <memory>
#include <string>

class Texture {
public:
    Texture(const char* filename);
    ~Texture();

    uint32_t GetWidth() const;
    uint32_t GetHeight() const;
    uint32_t GetID() const;

    void Bind(uint32_t slot = 0) const;

private:
    uint32_t id_{0};

    uint32_t width_{0};
    uint32_t height_{0};
};