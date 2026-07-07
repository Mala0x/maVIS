#include <cstddef>
#include <cstdint>
#include <cstring>
#include <ctime>
#include <fstream>
#include <optional>
#include <variant>
#include <vector>
#include <print>
#include <chrono>
#include "Instructions.hpp"
#include "FileFuncs.hpp"

// --- All my own hpp's are there because I want to use them in the future, first get the basics working here and then port them over for better modularity --- //

size_t pc = 0;

bool verbose_mode_set = false;

int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::println("You did not provide any file to be ran! Quitting \n");
        return -1;
    }
    
    if (argc == 3 && strcmp(argv[2], "-v") == 0) { // Check if we want to log to the console on each "cycle"!
        verbose_mode_set = true;
        std::println("Verbose mode is set to: {}", verbose_mode_set);
    }

    std::string inputFile(argv[1]); // Converting from char* to std::string for getting easy and safe string viewing options

    size_t fileExtension = inputFile.find(".mabin");

    if (fileExtension == std::variant_npos) {
        std::println("Your file is not in the correct format <filename>.mabin is expected! Quitting \n");
        return -1;
    }

    auto fileOptional = mavis::fileHandler::openFile(inputFile);

    std::fstream maBinFile;

    if (!fileOptional.has_value()) {
        std::println("Something has gone wrong in the opening of te file! Quitting \n");
        return -1;
    } else {
        maBinFile = std::move(fileOptional.value());
    }

    size_t fileSize = mavis::fileHandler::getFileSize(maBinFile);

    std::vector<uint8_t> flashMemory;

    std::array<uint16_t, 0xFF> registers;
    registers.fill(0);

    for (size_t i = 0; i < fileSize; ++i) {
        flashMemory.emplace_back(maBinFile.get());
    }

    while (pc < fileSize) {
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
                std::println("MOV has been called!\n");
                pc += 4; // This is ofc depending on if its a reg or IMM but I would check that in the function itself
                break;
            case 0x04:
                std::println("ADD has been called!\n");
                pc += 5;
        }
        if (verbose_mode_set) {std::println("[{:%T}]: We are logging multiple things each cycle!", std::chrono::system_clock::now());} // Maybe add more flags to kinda choose which "level" of logging you want
    }

    return 0;
}