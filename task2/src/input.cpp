#include "input.hpp"

constexpr size_t kMaxKeys = GLFW_KEY_LAST;

std::vector<bool> Keyboard::keys_pressed_(kMaxKeys, false);

bool Keyboard::Pressed(int key) {
    return keys_pressed_[key];
}

std::vector<bool>& Keyboard::GetKeys() {
    return keys_pressed_;
}