#include <cstddef>
#include <cstdint>
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

int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::println("You did not provide any file to be ran! Quitting \n");
        return -1;
    }

    std::string verboseMode(argv[2]);
    
    if (verboseMode.compare("-v") == 0) { // Check if we want to log to the console on each "cycle"!
        verbose_mode_set = true;
        std::println("Verbose mode is set to: {}", verbose_mode_set); // This stupid check will be substituted by an argument parser that I will eventually write
    }

    std::string inputFile(argv[1]); // Converting from char* to std::string for getting easy and safe string viewing options

    size_t fileExtension = inputFile.find(".mabin");

    mavis::fileHandler::isFileCorrectFormat(fileExtension);

    auto fileOptional = mavis::fileHandler::openFile(inputFile);

    std::fstream maBinFile;

    mavis::fileHandler::isFileValid(fileOptional, maBinFile);

    size_t fileSize = mavis::fileHandler::getFileSize(maBinFile);

    std::vector<uint8_t> flashMemory;

    std::array<uint16_t, 0xFF> registers;
    registers.fill(0);

    for (size_t i = 0; i < fileSize; ++i) {
        flashMemory.emplace_back(maBinFile.get());
    }

    auto time_at_beginning_program = std::chrono::system_clock::now();

    while (pc < fileSize) { // This is the big switch statement that is the heart of the entire program
        switch (flashMemory.at(pc)) {
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