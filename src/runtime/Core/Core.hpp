#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <vector>

class Core {
    private:
        // Variables & Constants
        const std::vector<uint8_t> &vector;
        std::array<uint16_t, 0xFF> registers{}; // Fill with 0 instead of random uncleaned garbage
        size_t program_counter = 0; // Set to zero for safety, made public to use with the Application class
        // Functions
        // 0. helpers
        uint16_t grab_addr_or_imm(uint16_t program_counter_offset);
        // 1. opcodes
        void nop();
        void jmp();
        void je();
        void mov_reg();
        void mov_imm();
        void add_reg();
        void add_imm();
        void cmp_reg();
        void cmp_imm();
        void sysc();
        // 2. Syscalls
        void sysc_0x0001();
        void sysc_0x0002();
    public:
        Core(const std::vector<uint8_t> &vector);
        void delegation();
        // Might want to add a headless delegation function
};