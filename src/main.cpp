#include <iostream>
#include "../build/Patty.hpp"

int main(int argc, char *argv[]) {
    if(argc < 2) {
        std::cout << argv[0] << " Version " << PATTY_VERSION_MAJOR << "." << PATTY_VERSION_MINOR << "." << PATTY_VERSION_PATCH << std::endl;
        std::cout << "Usage: " << argv[0] << " number" << std::endl;
        return 1;
    }
    return 0;
}
