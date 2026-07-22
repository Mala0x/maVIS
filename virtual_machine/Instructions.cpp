#include "Instructions.hpp"
#include <array>
#include <cstdint>
#include <print>

namespace {

    uint16_t grabAddrOrImm(size_t& pc, std::vector<uint8_t>& program, uint16_t pcOffset) {
        return (program[pc+(1+pcOffset)] << 8 | program[pc+(2+pcOffset)]);
    }

}

namespace mavis::instructions {

    void nop(size_t& pc) {
        std::printf("I am in the nop instruction!\n");
        pc += 1;
    }

    void jmp(size_t& pc, std::vector<uint8_t>& program) {
        std::println("We are in the jump function!");

        uint16_t bitshifted_args = grabAddrOrImm(pc, program, 0);

        if (bitshifted_args > program.size()) {
            std::println("The jmp function could not do its things because we are trying to jump to somewhere that is bigger then the program itself");
        }

        std::println("p1: 0x{:02x}, p2: 0x{:02x}, full: 0x{:04x}", program[pc+1], program[pc+2], bitshifted_args);

        pc = bitshifted_args;
    }

    void je(size_t& pc, std::vector<uint8_t>& program, std::array<uint16_t, 0xFF>& registers) {
        
        uint16_t addrToJmpTo = grabAddrOrImm(pc, program, 0);
        
        if (registers[0xF1]) {
            pc = addrToJmpTo;
            std::println("Jump is equal so we jump");
        } else {
            pc += 3;
            std::println("The jump was not equal so we did not jump");
        }

        std::println("je called, addr {}, zero_flag_value {}", addrToJmpTo, registers[0xF1]);

    }

    void mov_reg(size_t& pc, std::vector<uint8_t>& program, std::array<uint16_t, 0xFF>& registers) {

        registers[program[pc+1]] = registers[program[pc+2]];

        pc += 3;

        std::println("mov_reg called!");

    }

    void mov_imm(size_t& pc, std::vector<uint8_t>& program, std::array<uint16_t, 0xFF>& registers) {

        registers[program[pc+1]] = grabAddrOrImm(pc, program, 1);

        std::println("mov_imm whatToMove: {} mov_imm whereToMove: {}", registers[program[pc+1]], program[pc+1]);

        pc += 4;

        std::println("mov_imm called!");

    }

    void add_reg(size_t& pc, std::vector<uint8_t>& program, std::array<uint16_t, 0xFF>& registers) {

        uint32_t sum = static_cast<uint32_t>(registers[program[pc+1]]) + registers[program[pc+2]];

        if (sum > 0xFFFF) {
            std::println("Integer overflow detected!");
        } else {
            registers[program[pc+1]] += registers[program[pc+2]];
        }

        pc += 3;

        std::println("add_reg called!");

    }

    void add_imm(size_t& pc, std::vector<uint8_t>& program, std::array<uint16_t, 0xFF>& registers) {

        uint32_t sum = static_cast<uint32_t>(registers[program[pc+1]]) + grabAddrOrImm(pc, program, 1);

        std::println("p1: {}, p2: {}, sum: {}", (registers[program[pc+1]]), grabAddrOrImm(pc, program, 1), sum);

        if (sum > 0xFFFF) {
            std::println("Integer overflow detected!");
        } else {
            registers[program[pc+1]] += grabAddrOrImm(pc, program, 1);
        }

        pc += 4;

        std::println("add_imm called!");

    }

    void cmp_reg(size_t& pc, std::vector<uint8_t>& program, std::array<uint16_t, 0xFF>& registers) {

        uint16_t arg0Register = registers[program[pc+1]];
        uint16_t arg1Register = registers[program[pc+2]];

        if (arg0Register == arg1Register) {
            registers[0xF1] = 1;
        } else {
            registers[0xF1] = 0;
        }

        pc += 3;
        
    }
    
    void cmp_imm(size_t& pc, std::vector<uint8_t>& program, std::array<uint16_t, 0xFF>& registers) {

        uint8_t arg0RegIndex = program[pc+1];
        uint16_t arg0Register = registers[arg0RegIndex];
        uint16_t arg1Immediate = grabAddrOrImm(pc, program, 1);

        if (arg0Register == arg1Immediate) {
            registers[0xF1] = 1;
        } else {
            registers[0xF1] = 0;
        }

        pc += 4;

    }

}