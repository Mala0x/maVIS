#include "Core.hpp"

#include <vector>
#include <print>

std::vector<char> string_buffer;

void Core::sysc_0x0001() {
    string_buffer.emplace_back(this->registers[0x10]);
}

void Core::sysc_0x0002() {
    if (string_buffer.size() > 0) {
        std::println("{}", string_buffer.data());
        string_buffer.clear();
    } else {
        std::println("The string buffer is empty; not printing!");
    }
}