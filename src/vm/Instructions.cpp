#include "Instructions.hpp"
#include <array>
#include <cstdint>
#include <print>
#include "BackendAPI.hpp"

namespace { // Private functions only to be used within this file are placed here

    uint16_t grab_addr_or_imm(size_t& pc, std::vector<uint8_t>& program, uint16_t pc_offset) {
        return (program[pc + (1 + pc_offset)] << 8 | program[pc + (2 + pc_offset)]);
    }

}

namespace mavis::instructions {

    void nop(size_t& pc) {
        std::printf("I am in the nop instruction!\n");
        pc += 1;
    }

    void jmp(size_t& pc, std::vector<uint8_t>& program) {
        std::println("We are in the jump function!");

        uint16_t bitshifted_args = grab_addr_or_imm(pc, program, 0);

        if (bitshifted_args > program.size()) {
            std::println("The jmp function could not do its things because we are trying to jump to somewhere that is bigger then the program itself");
        }

        std::println("p1: 0x{:02x}, p2: 0x{:02x}, full: 0x{:04x}", program[pc + 1], program[pc + 2], bitshifted_args);

        pc = bitshifted_args;
    }

    void je(size_t& pc, std::vector<uint8_t>& program, std::array<uint16_t, 0xFF>& registers) {
        
        uint16_t addr_to_jmp_to = grab_addr_or_imm(pc, program, 0);
        
        if (registers[0xF1]) {
            pc = addr_to_jmp_to;
            std::println("Jump is equal so we jump");
        } else {
            pc += 3;
            std::println("The jump was not equal so we did not jump");
        }

        std::println("je called, addr {}, zero_flag_value {}", addr_to_jmp_to, registers[0xF1]);

    }

    void mov_reg(size_t& pc, std::vector<uint8_t>& program, std::array<uint16_t, 0xFF>& registers) {

        registers[program[pc + 1]] = registers[program[pc + 2]];

        pc += 3;

        std::println("mov_reg called!");

    }

    void mov_imm(size_t& pc, std::vector<uint8_t>& program, std::array<uint16_t, 0xFF>& registers) {

        registers[program[pc + 1]] = grab_addr_or_imm(pc, program, 1);

        std::println("mov_imm what_to_move: {} mov_imm where_to_move: {}", registers[program[pc + 1]], program[pc + 1]);

        pc += 4;

        std::println("mov_imm called!");

    }

    void add_reg(size_t& pc, std::vector<uint8_t>& program, std::array<uint16_t, 0xFF>& registers) {

        uint32_t sum = static_cast<uint32_t>(registers[program[pc + 1]]) + registers[program[pc + 2]];

        if (sum > 0xFFFF) {
            std::println("Integer overflow detected!");
        } else {
            registers[program[pc + 1]] += registers[program[pc + 2]];
        }

        pc += 3;

        std::println("add_reg called!");

    }

    void add_imm(size_t& pc, std::vector<uint8_t>& program, std::array<uint16_t, 0xFF>& registers) {

        uint32_t sum = static_cast<uint32_t>(registers[program[pc + 1]]) + grab_addr_or_imm(pc, program, 1);

        std::println("p1: {}, p2: {}, sum: {}", (registers[program[pc + 1]]), grab_addr_or_imm(pc, program, 1), sum);

        if (sum > 0xFFFF) {
            std::println("Integer overflow detected!");
        } else {
            registers[program[pc + 1]] += grab_addr_or_imm(pc, program, 1);
        }

        pc += 4;

        std::println("add_imm called!");

    }

    void cmp_reg(size_t& pc, std::vector<uint8_t>& program, std::array<uint16_t, 0xFF>& registers) {

        uint16_t arg0_register = registers[program[pc + 1]];
        uint16_t arg1_register = registers[program[pc + 2]];

        if (arg0_register == arg1_register) {
            registers[0xF1] = 1;
        } else {
            registers[0xF1] = 0;
        }

        pc += 3;
        
    }
    
    void cmp_imm(size_t& pc, std::vector<uint8_t>& program, std::array<uint16_t, 0xFF>& registers) {

        uint8_t arg0_reg_index = program[pc + 1];
        uint16_t arg0_register = registers[arg0_reg_index];
        uint16_t arg1_immediate = grab_addr_or_imm(pc, program, 1);

        if (arg0_register == arg1_immediate) {
            registers[0xF1] = 1;
        } else {
            registers[0xF1] = 0;
        }

        pc += 4;

    }

    void sysc(size_t& pc, std::vector<uint8_t>& program, std::array<uint16_t, 0xFF>& registers) {

        uint16_t syscall_number = grab_addr_or_imm(pc, program, 0);

        switch (syscall_number) { // All syscalls should be completely documented correctly AND syscalls are setup using the different registers no data is parsed to them via arguments
            case 0x0001:
                mavis::API::sysc_0x0001(registers);
                break;
            case 0x0002:
                mavis::API::sysc_0x0002();
                break;
            case 0x069:
                std::println("Hihi haha xDiddy");
                break;
            default:
                std::println("The syscall number you tried to use is not implemented yet (or you just used the wrong number)! Try again!");
                break;
        }

        pc += 3;

    }

}