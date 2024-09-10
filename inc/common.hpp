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


enum bind_type {LOC, GLO, EXT};

struct section{
    std::string _name;
    unsigned _base;
    unsigned _length;
    unsigned _lit_pool_base = 0;

    section(const std::string& name, unsigned base)
    : _name(name), _base(base) {}

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

    symbol(std::size_t num, int value, bind_type bind, std::string section_name, const std::string& name)
    : _num(num), _value(value), _bind(bind), _section_name(section_name), _name(name) {}  

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
    
};



#endif