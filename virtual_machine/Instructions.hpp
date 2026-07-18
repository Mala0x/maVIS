#pragma once
#include <cstddef>
#include <cstdint>
#include <vector>
#include <cstdio>

namespace mavis::instructions {
    void nop(size_t& pc);
    void jmp(size_t& pc, std::vector<uint8_t>& program);
    void je(size_t& pc, std::vector<uint8_t>& program, std::array<uint16_t, 0xFF>& registers);
    void mov_reg(size_t& pc, std::vector<uint8_t>& program, std::array<uint16_t, 0xFF>& registers);
    void mov_imm(size_t& pc, std::vector<uint8_t>& program, std::array<uint16_t, 0xFF>& registers);
    void add_reg(size_t& pc, std::vector<uint8_t>& program, std::array<uint16_t, 0xFF>& registers);
    void add_imm(size_t& pc, std::vector<uint8_t>& program, std::array<uint16_t, 0xFF>& registers);
}