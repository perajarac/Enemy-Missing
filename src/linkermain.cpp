#include "../inc/linker.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

void print_usage() {
    std::cerr << "Usage: ./linker -hex|-relocatable "
              << " optional: [-place=<section>@<address> [-place=<section>@<address> ...]] "
              << "-o <output_file> <input_files>...\n";
}

int main(int argc, char* argv[]) {
    if (argc < 5) {
        print_usage();
        return 1;
    }

    std::string first_arg = argv[1];
    if (first_arg != "-hex" && first_arg != "-relocatable") {
        std::cerr << "Error: First argument must be either '-hex' or '-relocatable'.\n";
        return 1;
    }

    // Store section placements
    std::vector<std::pair<std::string, int>> sections;
    std::vector<std::string> used_sections; 

    // Parse section placements and output file name
    std::string output_file;
    std::vector<std::string> input_files;

    for (int i = 2; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg.find("-place=") == 0) {
            // Extract section name and address
            size_t at_pos = arg.find('@');
            if (at_pos == std::string::npos) {
                std::cerr << "Error: Invalid format for '-place' argument.\n";
                return 1;
            }
            std::string section = arg.substr(7, at_pos - 7);
            std::string address_str = arg.substr(at_pos + 1);

            if(std::find(used_sections.begin(), used_sections.end(), section) != used_sections.end()){
                std::cerr << "Error: multiple section place.\n";
                return 1;
            }
            used_sections.push_back(section);
            int address = std::stoi(address_str, nullptr, 16);
            sections.push_back({section, address});
        } else if (arg == "-o") {
            if (i + 1 >= argc) {
                std::cerr << "Error: '-o' must be followed by an output file name.\n";
                return 1;
            }
            output_file = argv[++i];
        } else {
            input_files.push_back(arg);
        }
    }

    if (output_file.empty()) {
        std::cerr << "Error: Output file name not specified.\n";
        return 1;
    }

    // Check if the output file has the correct extension
    if(first_arg == "-hex") Linker::is_hex = true;
    std::string expected_extension = (first_arg == "-hex") ? ".hex" : ".o";
    if (output_file.size() < expected_extension.size() ||
        output_file.substr(output_file.size() - expected_extension.size()) != expected_extension) {
        std::cerr << "Error: Output file must end with '" << expected_extension << "'.\n";
        return 1;
    }

    std::sort(sections.begin(), sections.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
    return a.second < b.second;
    }); //sort -place sections by address

    Linker::set_output(output_file);
    Linker::set_input(input_files);
    Linker::set_place_sections(sections);

    Linker::read_obj_files();
    Linker::merge_same_sections();
    Linker::map_sections();
    Linker::print_sections_and_mem_content();

    return 0;
}
