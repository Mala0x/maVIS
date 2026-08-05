#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <vector>
#include <print>
#include <chrono>
#include "Instructions.hpp"
#include "FileFuncs.hpp"

// --- All my own hpp's are there because I want to use them in the future, first get the basics working here and then port them over for better modularity --- //

// I do also get the feeling I might need to start writing my own argument parser for the cpp virtual machine side of this project
// I do have multiple things I want the user to be able to configure before starting the execution of said program

size_t pc = 0; // This is the program counter AKA the pointer into memory where we are atm

bool verbose_mode_set = false; // This defaults to false because no one wants to be logging at default (I think atleast)

// I am just grabbing some core stuff from the main function and putting them into their own functions for better readability

void is_file_provided(int argc) { // sub this eventaully with my own argument parser but for now this is aight
    if (argc < 2) {
        std::println("No file was provided, quitting! Usage: ./program fileName.mabin");
        exit(EXIT_FAILURE);
    }
}

void set_verbose_mode(char* verbose_mode_arg_flag, bool *verbose_mode_flag) {

    std::string verbose_mode_flag_string(verbose_mode_arg_flag); // Moved the string in his own function so it destroys itself after checking because there is no need to keep it around the entire time the vm is running

    if (verbose_mode_flag_string.compare("-v") == 0) {
        *verbose_mode_flag = true;
        std::println("Verbose mode is set to: {}", *verbose_mode_flag);
    }
}

int main(int argc, char* argv[]) {

    is_file_provided(argc);
    
    set_verbose_mode(argv[2], &verbose_mode_set); // Again a simple error prone argument parser thing that eventaully will be replaced by my own parser

    // Need to optimize this and move this all into the fileHandler

    std::string inputFile(argv[1]); // Converting from char* to std::string for getting easy and safe string viewing options

    size_t fileExtension = inputFile.find(".mabin");

    mavis::fileHandler::isFileCorrectFormat(fileExtension); // Might make it so you only have to give the string and do not have to also do the size_t fileExtension thing

    // Need to optimize this and move this all into the fileHandler

    auto fileOptional = mavis::fileHandler::openFile(inputFile);

    std::fstream maBinFile;

    mavis::fileHandler::isFileValid(fileOptional, maBinFile);

    size_t fileSize = mavis::fileHandler::getFileSize(maBinFile);

    // Maybe check if we can combine the upper 4 function calls into just one function call to the outside and do all the validation inside the fileHandler 

    std::vector<uint8_t> flashMemory;

    std::array<uint16_t, 0xFF> registers;
    registers.fill(0);

    for (size_t i = 0; i < fileSize; ++i) {
        flashMemory.emplace_back(maBinFile.get());
    }

    std::chrono::time_point time_at_beginning_program = std::chrono::system_clock::now(); // This for now will always show TODO: eventually put this behind the verbose mode flag

    while (pc < fileSize) { // This is the big switch statement that is the heart of the entire program
        switch (flashMemory.at(pc)) { // Maybe move this into its own like loop() function so the int main function stays clean but that might induce a big headache
            case 0x00:
                mavis::instructions::nop(pc);
                break;
            case 0x01:
                mavis::instructions::jmp(pc, flashMemory);
                break;
            case 0x02:
                mavis::instructions::je(pc, flashMemory, registers);
                break;
            case 0x03:
                mavis::instructions::mov_reg(pc, flashMemory, registers);
                break;
            case 0x04:
                mavis::instructions::mov_imm(pc, flashMemory, registers);
                break;
            case 0x05:
                mavis::instructions::add_reg(pc, flashMemory, registers);
                break;
            case 0x06:
                mavis::instructions::add_imm(pc, flashMemory, registers);
                break;
            case 0x07:
                mavis::instructions::cmp_reg(pc, flashMemory, registers);
                break;
            case 0x08:
                mavis::instructions::cmp_imm(pc, flashMemory, registers);
                break;
            case 0x09:
                mavis::instructions::sysc(pc, flashMemory);
                break;
        }

        if (verbose_mode_set) {std::println("[{:%T}]: Something has happened and I logged it :) (This ofc should become better and actually give usefull information)", std::chrono::system_clock::now());} // Maybe add more flags to kinda choose which "level" of logging you want
    }

    if (verbose_mode_set) { // These are all the things worthy of logging when the program finished running
        for (size_t i = 0; i <= 10; ++i) {
                std::println("register{}: {}", 0x10*i, registers[0x10*i]);
        }

        std::println("zero_flag register: {}", registers[0xF1]);

        std::println("Total time taken for the main loop to execute: [{:%T}]", (std::chrono::system_clock::now() - time_at_beginning_program));
    }  

    return 0;
}