#pragma once

#include <vector>
#include <GLFW/glfw3.h>

class Keyboard {
 private:
  Keyboard() = default;

 public:
  static bool Pressed(int key);
  static std::vector<bool>& GetKeys();

 private:
  static std::vector<bool> keys_pressed_;
};