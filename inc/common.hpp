#ifndef _common_hpp_
#define _common_hpp_
#include <string>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <memory>
#include <unordered_map>
#include <algorithm>
#include <unordered_set>
#include <map>
#include <sys/mman.h>
#include <iostream>
#include <cstring>


enum bind_type {LOC, GLO, EXT};

struct reloc_node{
    int offset;
    std::string symbol_name;
    int addend;
    bool is_section;
};

struct section{
    std::string _name;
    unsigned _base;
    unsigned _length;
    unsigned _lit_pool_base = 0;
    std::vector<reloc_node> relocation_table;

    std::vector<std::pair<int, std::string>> memory_content;


    section() = default;

    section(const std::string& name, unsigned base)
    : _name(name), _base(base) {}

    section(std::string name, unsigned base, unsigned length, unsigned literal_pool_base)
    :_name(name), _base(base), _length(length), _lit_pool_base(literal_pool_base) {}

    unsigned get_length() const;
    unsigned get_base() const;
    std::string get_name() const;
    unsigned get_lit_pool_base() const;

    void set_length(unsigned length);
    void set_lit_pool_base(unsigned lit_pool_base);


};

struct symbol{
    std::size_t _num;
    int _value;
    bind_type _bind;
    std::string _section_name;
    std::string _name;
    static int id;

    symbol() = default;

    symbol(std::size_t num, int value, bind_type bind, std::string section_name, const std::string& name)
    : _num(num), _value(value), _bind(bind), _section_name(section_name), _name(name) {}  

    symbol(int value, bind_type bind, std::string section_name, const std::string& name)
    : _value(value), _bind(bind), _section_name(section_name), _name(name) {_num = id++;}  

    unsigned get_num() const;
    int get_value() const;
    bind_type get_bind() const;
    std::string get_section_name() const;
    std::string get_name() const;

    void set_num(unsigned num);
    void set_value(unsigned value);
    void set_bind(bind_type bind);
    void set_section_name(const std::string sec_name);
    void set_name(const std::string name);

    friend std::ostream& operator<<(std::ostream& os, const symbol& obj){
        return os << obj.get_name() << std::endl;
    }

    bool operator==(const symbol& other) const {
        return this->_name == other._name;  
    }
};

struct file{
    std::vector<section> section_tables;
    std::vector<symbol> sym_table;
    std::vector<std::pair<int, std::string>> memory_content;

    void add_section(section sec);
    void add_symbol(symbol sym);
};

extern int count_sec_length(const std::vector<section>& vec);


enum op_codes{
    HALT = 0x00,
    INT = 0x10,
    CALL_IMM = 0x20,
    CALL_MEM = 0x21,
    JMP_IMM = 0x30,
    BEQ_IMM = 0x31,
    BNE_IMM = 0x32,
    BGT_IMM = 0x33,
    JMP_MEM = 0x38,
    BEQ_MEM = 0x39,
    BNE_MEM = 0x3A,
    BGT_MEM = 0x3B,
    XCHG = 0x40,
    ADD = 0x50,
    SUB = 0x51,
    MUL = 0x52,
    DIV = 0x53,
    NOT = 0x60,
    AND = 0x61,
    OR = 0x62,
    XOR = 0x63,
    SHL = 0x70,
    SHR = 0x71,
    ST_MEM = 0x80,
    ST_MEM_MEM = 0x82,
    PUSH = 0x81,
    CSRRD = 0x90,
    LD_REG = 0x91,
    LD_MEM_REG = 0x92,
    POP = 0x93,
    CSRWR = 0x94,
    CSRWR_OR = 0x95,
    CSRWR_MEM = 0x96,
    CSRWR_MEM_POSTINC = 0x97
  };


  enum gpr{
    r0 = 0,
    r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, r15,
    sp = 14,
    pc = 15
  };

  enum csr{
    status = 0,
    handler,
    cause
  };



#endif