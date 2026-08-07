#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <print>
#include <chrono>
#include <optional>
#include "Instructions.hpp"
#include "FileFuncs.hpp"

// --- All my own hpp's are there because I want to use them in the future, first get the basics working here and then port them over for better modularity --- //

// I do also get the feeling I might need to start writing my own argument parser for the cpp virtual machine side of this project
// I do have multiple things I want the user to be able to configure before starting the execution of said program

size_t program_counter = 0; // This is the program counter AKA the pointer into memory where we are atm

bool verbose_mode_set = false; // This defaults to false because no one wants to be logging at default (I think atleast)

// I am just grabbing some core stuff from the main function and putting them into their own functions for better readability

void is_file_provided(int argc) { // sub this eventaully with my own argument parser but for now this is aight
    if (argc < 2) {
        std::println("No file was provided, quitting! Usage: ./program fileName.mabin");
        exit(EXIT_FAILURE);
    }
}

void set_verbose_mode(char *verbose_mode_arg_flag, bool *verbose_mode_flag) {

    if (verbose_mode_arg_flag == nullptr) { // if the flag is not given then just skip this check and allocation
        return;
    }

    std::string verbose_mode_flag_string(verbose_mode_arg_flag); // Moved the string in his own function so it destroys itself after checking because there is no need to keep it around the entire time the vm is running

    if (verbose_mode_flag_string.compare("-v") == 0) {
        *verbose_mode_flag = true;
        std::println("Verbose mode is set to: {}", *verbose_mode_flag);
    }

}

void check_command_line_args(int argc, char *verbose_mode_arg_flag, bool *verbose_mode_flag) {
    is_file_provided(argc);
    set_verbose_mode(verbose_mode_arg_flag, verbose_mode_flag);
}

int main(int argc, char* argv[]) {

    check_command_line_args(argc, argv[2], &verbose_mode_set); // These kinda multifunctions should be the only (or atleast) as least as possible publicly facing functions

    std::vector<uint8_t> flash_memory;

    mavis::fileHandler::place_file_in_flash_memory(argv[1], &flash_memory);

    std::array<uint16_t, 0xFF> registers;
    registers.fill(0); // Just fill everything with a zero so we do not have garbo data that hasnt been cleaned up nicely

    std::optional<std::chrono::system_clock::time_point> time_at_beginning_program; // Make this an optional because otherwise you assign a good amount of space for something that is never used

    if (verbose_mode_set) {
        time_at_beginning_program = std::chrono::system_clock::now();
    }

    while (program_counter < flash_memory.size()) { // This is the big switch statement that is the heart of the entire program
        switch (flash_memory.at(program_counter)) { // Maybe move this into its own like loop() function so the int main function stays clean but that might induce a big headache
            case 0x00:
                mavis::instructions::nop(program_counter);
                break;
            case 0x01:
                mavis::instructions::jmp(program_counter, flash_memory);
                break;
            case 0x02:
                mavis::instructions::je(program_counter, flash_memory, registers);
                break;
            case 0x03:
                mavis::instructions::mov_reg(program_counter, flash_memory, registers);
                break;
            case 0x04:
                mavis::instructions::mov_imm(program_counter, flash_memory, registers);
                break;
            case 0x05:
                mavis::instructions::add_reg(program_counter, flash_memory, registers);
                break;
            case 0x06:
                mavis::instructions::add_imm(program_counter, flash_memory, registers);
                break;
            case 0x07:
                mavis::instructions::cmp_reg(program_counter, flash_memory, registers);
                break;
            case 0x08:
                mavis::instructions::cmp_imm(program_counter, flash_memory, registers);
                break;
            case 0x09:
                mavis::instructions::sysc(program_counter, flash_memory, registers);
                break;
        }

        if (verbose_mode_set) {std::println("[{:%T}]: Something has happened and I logged it :) (This ofc should become better and actually give usefull information)", std::chrono::system_clock::now());} // Maybe add more flags to kinda choose which "level" of logging you want
    }

    if (verbose_mode_set) { // These are all the things worthy of logging when the program finished running
        for (size_t i = 0; i <= 10; ++i) {
                std::println("register{}: {}", 0x10*i, registers[0x10*i]);
        }
        std::println("zero_flag register: {}", registers[0xF1]);
        std::println("Total time taken for the main loop to execute: [{:%T}]", (std::chrono::system_clock::now() - time_at_beginning_program.value())); // I never have to check if the optional has a value because I always give it a value when verbose mode is set and I only grab the value when verbose mode is set
    }  

    return 0;
}