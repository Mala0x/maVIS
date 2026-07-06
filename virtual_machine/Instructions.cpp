#include "Instructions.hpp"
#include <array>
#include <cstdint>
#include <print>

namespace {
    uint16_t grabMemoryAddress(size_t& pc, std::vector<uint8_t>& program) {
        return (program[pc+1] << 8 | program[pc+2]);
    }
}

namespace mavis::instructions {

    void nop(size_t& pc) {
        std::printf("I am in the nop instruction!\n");
        pc += 1;
    }

    void jmp(size_t& pc, std::vector<uint8_t>& program) {
        std::println("We are in the jump function!");

        uint16_t bitshifted_args = grabMemoryAddress(pc, program);

        std::println("p1: 0x{:02x}, p2: 0x{:02x}, full: 0x{:04x}", program[pc+1], program[pc+2], bitshifted_args);

        pc += 3;
    }
 
    void je(size_t& pc, std::vector<uint8_t>& program, std::array<uint8_t, 0xFF>& registers) {
        
        uint16_t addrToJmpTo = grabMemoryAddress(pc, program);
        
        if (registers[0xF1]) {
            pc = addrToJmpTo;
        } else {
            pc += 3;
        }

        std::println("je called, addr {}, register {}", addrToJmpTo, registers[0xF1]);

    }

    void mov(size_t& pc, std::vector<uint8_t>& program) {

    }

    void add(size_t& pc, std::vector<uint8_t>& program) {
        
    }

}