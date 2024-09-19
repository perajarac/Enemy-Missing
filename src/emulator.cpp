#include "../inc/emulator.hpp"


std::vector<int> Emulator::gprs(15,0);
std::vector<int> Emulator::csrs(3,0);
int& Emulator::sp = gprs[14];
int& Emulator::pc = gprs[15];

void* Emulator::memory;
std::string Emulator::obj_hex;

void Emulator::read_obj(){
    if(obj_hex == ""){
        std::cerr << "Error, no input file\n";
        exit(-1);
    }

    
}