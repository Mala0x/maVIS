#include "Core.hpp"

/*
In this file the only the helper functions, delegation and some other
misc things will be defined to keep it tidy
*/

#include <cstdint>
#include <print>

Core::Core(const std::vector<uint8_t> &vector) : vector(vector) {
    std::println("VERBOSE: Program size: {}", this->vector.size());
}

uint16_t Core::grab_addr_or_imm(uint16_t program_counter_offset) {
    size_t base = this->program_counter + program_counter_offset;
    return static_cast<uint16_t>(this->vector[base + 1] << 8 | this->vector[base + 2]);
}

void Core::delegation() {
    while (this->program_counter < this->vector.size()) {
        switch (this->vector.at(this->program_counter)) {
            case 0x00:
                this->nop();
                break;
            case 0x01:
                this->jmp();
                break;
            case 0x02:
                this->je();
                break;
            case 0x03:
                this->mov_reg();
                break;
            case 0x04:
                this->mov_imm();
                break;
            case 0x05:
                this->add_reg();
                break;
            case 0x06:
                this->add_imm();
                break;
            case 0x07:
                this->cmp_reg();
                break;
            case 0x08:
                this->cmp_imm();
                break;
            case 0x09:
                this->sysc();
                break;
            default:
                std::println("Unknown opcode encountered: 0x{:02x} at PC: {}", this->vector.at(this->program_counter), this->program_counter);
        }
    }
}