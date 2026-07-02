#include "Instructions.hpp"
#include <print>

namespace mavis::instructions {

    void nop(size_t& pc) {
        std::printf("I am in the nop instruction!\n");
        pc += 1;
    }

    void jmp(size_t& pc, std::vector<uint8_t>& program) {
        std::println("Where are in the jump function!");

        uint16_t bitshifted_args = (program[pc+1] << 8 | program[pc+2]);

        std::println("p1: 0x{:02x}, p2: 0x{:02x}, full: 0x{:04x}", program[pc+1], program[pc+2], bitshifted_args);

        pc += 3;
    }

}