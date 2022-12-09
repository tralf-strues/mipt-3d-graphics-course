#include "texture.hpp"

#include <cassert>
#include <stb_image/stb_image.h>

Texture::Texture(const char* filename) {
    stbi_set_flip_vertically_on_load(true);

    int32_t width, height, channels;
    uint8_t* data = stbi_load(filename, &width, &height, &channels, /*desired_channels=*/0);
    assert(data);

    GLenum internal_format = 0;
    GLenum data_format = 0;

    switch (channels) {
        case 4: {
            internal_format = GL_RGBA8;
            data_format = GL_RGBA;
            break;
        }

        case 3: {
            internal_format = GL_RGB8;
            data_format = GL_RGB;
            break;
        }

        default: {
            assert(!"Invalid number of image channels!");
        }
    }

    width_ = width;
    height_ = height;

    glGenTextures(1, &id_);
    glBindTexture(GL_TEXTURE_2D, id_);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, /*level=*/0, internal_format, width, height, /*border=*/0, data_format,
                 GL_UNSIGNED_BYTE, data);

    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
}

Texture::~Texture() {
    glDeleteTextures(1, &id_);
}

uint32_t Texture::GetWidth() const {
    return width_;
}

uint32_t Texture::GetHeight() const {
    return height_;
}

uint32_t Texture::GetID() const {
    return id_;
}

void Texture::Bind(uint32_t slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, id_);
}
