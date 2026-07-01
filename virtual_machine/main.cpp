#include <cstddef>
#include <cstdint>
#include <exception>
#include <fstream>
#include <iostream>
#include <optional>
#include <variant>
#include <vector>

// --- All my own hpp's are there because I want to use them in the future, first get the basics working here and then port them over for better modularity --- //


std::optional<std::fstream> openFile(std::string fileName) {

    std::fstream maBinFile;

    try {
        maBinFile.open(fileName, std::ios::in | std::ios::binary);
    } catch(std::exception e) {
        std::cout << e.what() << std::endl;
        return {};
    }

    return maBinFile;
}

size_t getFileSize(std::fstream& maBinFile) {
    maBinFile.seekg(0, std::ios::end);
    size_t fileSize = maBinFile.tellg();
    maBinFile.seekg(0, std::ios::beg);
    return fileSize;
}

void __JMP_INSTRUCTION(std::vector<uint8_t>& application, size_t& pc) {
    std::printf("We are in the __JMP_INSTRUCTION function!\n");

    // The comments are for an example so i can mentally map this out this does not reflect what I am using to test right now

    uint16_t bitshifted_args = (application[pc+1] << 8 | application[pc+2]);

    std::printf("%02x\n", application[pc+1]);
    std::printf("%02x\n", application[pc+2]);

    std::printf("Full addy: 0x%04x\n", bitshifted_args);

    pc += 3; // So we can go to the next opcode

}

size_t pc = 0;

int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::printf("You did not provide any file to be ran! Quitting \n");
        return -1;
    }

    std::string inputFile(argv[1]); // Converting from char* to std::string for getting easy and safe string viewing options

    size_t fileExtension = inputFile.find(".mabin");

    if (fileExtension == std::variant_npos) {
        std::printf("Your file is not in the correct format <filename>.mabin is expected! Quitting \n");
        return -1;
    }

    auto fileOptional = openFile(inputFile);

    std::fstream maBinFile;

    if (!fileOptional.has_value()) {
        std::printf("Something has gone wrong in the opening of te file! Quitting \n");
        return -1;
    } else {
        maBinFile = std::move(fileOptional.value());
    }

    size_t fileSize = getFileSize(maBinFile);

    std::vector<uint8_t> flashMemory;

    for (size_t i = 0; i < fileSize; ++i) {
        flashMemory.emplace_back(maBinFile.get());
    }

    while (pc < fileSize) {
        switch (flashMemory.at(pc)) {
            case 0x00:
                std::printf("NOP has been called!\n");
                pc++;
                break;
            case 0x01:
                __JMP_INSTRUCTION(flashMemory, pc);
                break;
            case 0x02:
                std::printf("JE has been called!\n");
                pc += 3;
                break;
            case 0x03:
                std::printf("MOV has been called!\n");
                pc += 4; // This is ofc depending on if its a reg or IMM but I would check that in the function itself
                break;
            case 0x04:
                std::printf("ADD has been called!\n");
                pc += 5;
        }
    }

    return 0;
}