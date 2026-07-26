#include "BackendAPI.hpp"
#include <print>

namespace mavis::API {
    void sysc0x0001() {
        std::println("This is the syscall 0x0001");
    }
}