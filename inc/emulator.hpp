#ifndef _emulator_hpp_
#define _emulator_hpp_

#include "common.hpp"

class Emulator{

public:

    static void read_obj();

    static void set_input(const std::string& in_obj){
        obj_hex = in_obj;
    }


    static constexpr long start_memory = 0x40000000;
    static constexpr long memory_size = 1L<<32;
    static constexpr long mmap_registers_addr = 0x0FFFFFF00;
    static constexpr int ins_fault = 0x1;
    static constexpr int terminal_int = 0x3;
    static constexpr int term_in = 0x0FFFFFF04;
    static constexpr int term_out = 0x0FFFFFF00;
    static constexpr int soft_int = 0x4;

    static void map_memory();
    static void lae_ins();
    static void mk_interrupt(int);
    static void write_reg();
    static void setup();

    static bool end(){
        return emulating == false;
    }


private:

    static void push(int data);
    static int pop();

    static void write(int addr, int data);
    static int read(int addr);
    

    static std::vector<int> gprs;
    static int& sp;
    static int& pc;
    static std::vector<int> csrs;
    static std::map<int,char> memory;
    
    static std::string obj_hex;
    static std::vector<section> sections;

    static bool emulating;

};

#endif