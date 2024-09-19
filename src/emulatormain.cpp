#include "../inc/emulator.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file.hex>" << std::endl;
        return 1;
    }

    std::string hex_file = argv[1];

    if (hex_file.size() < 4 || hex_file.substr(hex_file.size() - 4) != ".hex") {
        std::cerr << "Error: File must have a .hex extension." << std::endl;
        return 1;
    }

    Emulator::set_input(hex_file);
    Emulator::read_obj();
    Emulator::map_memory();


    return 0;
}