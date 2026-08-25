#include "Core.hpp"

#include <print>
#include <cstdlib>

void Core::nop() {
    //std::println("NOP CALLED!");
    this->program_counter += 1;
}

void Core::jmp() {
    //std::println("JMP CALLED!");

    uint16_t addr = this->grab_addr_or_imm(0);

    if (addr > this->vector.size()) {
        std::println("The jmp function tried to jump to something out of bounds!");
        std::exit(-1); // Has to be handled better
    } else {
        this->program_counter = addr;
    }
}

void Core::je() {
    std::println("JE CALLED!");

    uint16_t addr = this->grab_addr_or_imm(0);

    if (this->registers[0xF1]) {
        this->program_counter = addr;
        std::println("It is equal so we jump!");
    } else {
        this->program_counter += 3;
        std::println("It is not equal we did not jump");
    }
}

void Core::mov_reg() {
    std::println("MOV_REG CALLED!");

    uint8_t dst_reg = this->vector[this->program_counter + 1];
    uint8_t src_reg = this->vector[this->program_counter + 2];

    this->registers[dst_reg] = this->registers[src_reg];
    this->program_counter += 3;
}

void Core::mov_imm() {
    std::println("MOV_IMM CALLED!");

    uint8_t dst_reg = this->vector[this->program_counter + 1];
    uint16_t imm = this->grab_addr_or_imm(1);

    this->registers[dst_reg] = imm;
    this->program_counter += 4;
}

void Core::add_reg() {
    std::println("ADD_REG CALLED!");

    uint8_t dst_reg = this->vector[this->program_counter + 1];
    uint8_t src_reg = this->vector[this->program_counter + 2];

    uint32_t sum = static_cast<uint32_t>(this->registers[dst_reg]) + this->registers[src_reg];

    if (sum > 0xFFFF) {
        std::println("Integer overflow detected!");
    } else {
        this->registers[dst_reg] += this->registers[src_reg];
    }

    this->program_counter += 3;
}

void Core::add_imm() {
    std::println("ADD_IMM CALLED!");

    uint8_t dst_reg = this->vector[this->program_counter + 1];
    uint16_t imm = this->grab_addr_or_imm(1);

    uint32_t sum = static_cast<uint32_t>(this->registers[dst_reg]) + imm;

    if (sum > 0xFFFF) {
        std::println("Integer overflow detected!");
    } else {
        this->registers[dst_reg] += imm;
    }

    this->program_counter += 4;
}

void Core::cmp_reg() {
    std::println("CMP_REG CALLED!");

    uint8_t reg1 = this->vector[this->program_counter + 1];
    uint8_t reg2 = this->vector[this->program_counter + 2];

    if (this->registers[reg1] == this->registers[reg2]) {
        this->registers[0xF1] = 1;
    } else {
        this->registers[0xF1] = 0;
    }

    this->program_counter += 3;
}

void Core::cmp_imm() {
    std::println("CMP_IMM CALLED!");

    uint8_t reg = this->vector[this->program_counter + 1];
    uint16_t imm = this->grab_addr_or_imm(1);

    if (this->registers[reg] == imm) {
        this->registers[0xF1] = 1;
    } else {
        this->registers[0xF1] = 0;
    }

    this->program_counter += 4;
}

void Core::sysc() {
    std::println("SYSC CALLED!");

    uint16_t syscall_number = this->grab_addr_or_imm(0);

    switch (syscall_number) {
        case 0x0001:
            Core::sysc_0x0001();
            break;
        case 0x0002:
            Core::sysc_0x0002();
            break;
        case 0x0069:
            std::println("Hihi haha xDiddy");
            break;
        default:
            std::println("Unimplemented or invalid syscall number: 0x{:04x}", syscall_number);
            break;
    }

    this->program_counter += 3;
}