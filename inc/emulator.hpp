#ifndef _emulator_hpp_
#define _emulator_hpp_

#include "common.hpp"

class Emulator{

public:

    static void read_obj();

    static void set_input(const std::string& in_obj){
        obj_hex = in_obj;
    }

    struct place_section{
        unsigned int base;
        int size;
        std::map<int, std::string> memory_content;
    };


    static constexpr int start_memory = 0x40000000;
    static constexpr long memory_size = 1L<<32;
    static constexpr int mmap_registers_addr = 0x0FFFFFF00;
    static constexpr int ins_fault = 0x1;
    static constexpr int terminal_int = 0x3;
    static constexpr int term_in = 0x0FFFFFF04;
    static constexpr int term_out = 0x0FFFFFF00;
    static constexpr int soft_int = 0x4;

private:
    static std::vector<int> gprs;
    static int& sp;
    static int& pc;
    static std::vector<int> csrs;
    static void* memory;
    
    static std::string obj_hex;

};




#endif