#pragma once
#include <array>
#include <cstdint>

namespace mavis::API {
    void sysc_0x0001(std::array<uint16_t, 0xFF>& registers); // syscall for saving what is in register R1 to string-buffer according to the ascii table
    void sysc_0x0002();
}