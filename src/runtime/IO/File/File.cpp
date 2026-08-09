#include "File.hpp"

#include <exception>
#include <print>
// This class parses the file into the std::vector and return that 
/*
This file parses the file and puts it into a vector
This ofc also checks all kinda stuff that could go horribly wrong
*/

File::File(Config &application_config) : application_config(application_config) {

    File::file_in_vector();

    std::println("The file I am going to parse and to shit with is = {}", this->application_config.mabin_file);
}

void File::open_file() {
    try {
        this->ma_bin_file.open(this->application_config.mabin_file, std::ios::in | std::ios::binary);
    } catch(std::exception e) {
        std::println("{}", e.what());
        exit(-1); // Check if this results into a type otherwise exit the program
    } // Above line might not be needed because it default inits to {}
}

size_t File::get_file_size() {
    this->ma_bin_file.seekg(0, std::ios::end);
    size_t file_size = this->ma_bin_file.tellg(); // Save the value for return
    this->ma_bin_file.seekg(0, std::ios::beg); // Set the cursor back to the beginning of the file
    return file_size;
}

void File::file_in_vector() {
    File::open_file();
    
    const size_t file_size = File::get_file_size();

    this->vector.resize(file_size);

    this->ma_bin_file.read(reinterpret_cast<char*>(this->vector.data()), file_size);
}