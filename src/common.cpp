#include "../inc/common.hpp"

int symbol::id = 0;

// symbol class member functions
unsigned symbol::get_num() const {
    return _num;
}

int symbol::get_value() const {
    return _value;
}

bind_type symbol::get_bind() const {
    return _bind;
}

std::string symbol::get_name() const {
    return _name;
}

void symbol::set_num(unsigned num) {
    _num = num;
}

void symbol::set_value(unsigned value) {
    _value = value;
}

void symbol::set_bind(bind_type bind) {
    _bind = bind;
}

std::string symbol::get_section_name() const {
    return _section_name;
}

void symbol::set_section_name(const std::string section_name) {
    _section_name = section_name;
}

void symbol::set_name(const std::string name) {
    _name = name;
}

// section class member functions
unsigned section::get_length() const {
    return _length;
}

unsigned section::get_base() const {
    return _base;
}

std::string section::get_name() const {
    return _name;
}

void section::set_length(unsigned length) {
    _length = length;
}

unsigned section::get_lit_pool_base() const {
    return _lit_pool_base;
}

void section::set_lit_pool_base(unsigned lit_pool_base) {
    _lit_pool_base = lit_pool_base;
}

void file::add_section(section sec) {
    section_tables.push_back(sec);
}

void file::add_symbol(symbol sym) {
    sym_table.push_back(sym);
}

int count_sec_length(const std::vector<section>& vec){
    int sum_length = 0;
    for(const auto& sec:vec){
        sum_length += sec.get_length();
    }
    return sum_length;
}

char hex_to_string(const std::string& hex_string){
    unsigned int byte;
        std::stringstream ss;
        ss << std::hex << hex_string;
        ss >> byte;
        return static_cast<unsigned char>(byte);
}
