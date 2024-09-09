#include "../inc/linker.hpp"


std::vector<std::pair<std::string,std::string>> Linker::place_sections;
std::vector<std::string> Linker::input_files;
std::string Linker::output_file;



void Linker::set_input(std::vector<std::string> in){
    input_files = in;
}
void Linker::set_output(std::string out){
    output_file = out;
}


void Linker::set_place_sections(std::vector<std::pair<std::string,std::string>> ps){
    place_sections = ps;
}