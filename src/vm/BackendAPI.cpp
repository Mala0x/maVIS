#include "BackendAPI.hpp"
#include <print>
#include <vector>

std::vector<char> string_buffer;

namespace mavis::API {
    void sysc_0x0001(std::array<uint16_t, 0xFF>& registers) { // syscall for saving what is in register R1 to string-buffer according to the ascii table
        string_buffer.emplace_back(registers[0x10]); // You have to add the null terminator yourself in this version otherwise bullcrap will be printed
    }

    void sysc_0x0002() { // syscall for printing the string buffer to the terminal and flushing the buffer
        
        if (string_buffer.size() > 0) { // When buffer is empty DO NOT PRINT BAD BAD will happen
            std::println("{}", string_buffer.data());
            string_buffer.clear();
        } else {
            std::println("The string buffer is empty, not printing anything besides this error message!");
        }
    }
}