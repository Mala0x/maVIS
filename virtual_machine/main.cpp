#include <cstddef>
#include <cstdint>
#include <exception>
#include <fstream>
#include <iostream>
#include <optional>
#include <vector>

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

size_t pc = 0;

int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::printf("You did not provide any file to be ran! Quitting \n");
        return -1;
    }

    std::string inputFile(argv[1]);

    size_t fileExtension = inputFile.find(".mabin");

    if (fileExtension < 1 || fileExtension > 56) {
        std::printf("Your file does not have the correct file extension (or your filename is bigger then 50 characters (that's to much man chill out) )! Quitting \n");
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
                std::printf("JMP has been called!\n");
                pc += 3;
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