#pragma once
#include <cstddef>
#include <cstdint>
#include <vector>
#include <cstdio>

namespace mavis::instructions {

    void nop(size_t& pc);
    void jmp(size_t& pc, std::vector<uint8_t>& program);
    void je(size_t& pc, std::vector<uint8_t>& program, std::array<uint8_t, 0xFF>& registers);
    void mov(size_t& pc, std::vector<uint8_t>& program);
    void add(size_t& pc, std::vector<uint8_t>& program);

}