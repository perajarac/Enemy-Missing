#include "../inc/assembler.hpp"


std::vector<Assembler::section> Assembler::section_tables;
std::vector<Assembler::symbol> Assembler::sym_table;
std::vector<std::pair<unsigned, std::string>> Assembler::memory_content;
std::unordered_map<std::string, std::vector<Assembler::flink>> Assembler::flink_table;

std::ofstream  Assembler::ass_output;
unsigned Assembler::current_address = 0;
unsigned Assembler::location_counter = 0;

void Assembler::make_section(std::string& section_name){
    if(section_tables.size()>0) end_last_section();
    section new_section(section_name,current_address);
    section_tables.push_back(new_section);
}


void Assembler::handle_instruction(instruction op_code, std::vector<int> operands){
    switch(op_code){
        case HALT_CODE:{
            for(int i = 0; i<4;i++){
                std::pair<unsigned, std::string> to_add = std::make_pair(current_address++, "00");
                memory_content.push_back(to_add);
            }
            break;
        }
        case INT_CODE:{
            std::pair<unsigned, std::string> to_add = std::make_pair(current_address++, "01");
            memory_content.push_back(to_add);
            for(int i = 0; i<3;i++){
                std::pair<unsigned, std::string> to_add = std::make_pair(current_address++, "00");
                memory_content.push_back(to_add);
            }
            break;

        }
        case ADD_CODE:{
            arithmetic_operation("50",operands);
            break;
        }
        case SUB_CODE:{
            arithmetic_operation("51",operands);
            break;
        }case MUL_CODE:{
            arithmetic_operation("52",operands);
            break;
        }case DIV_CODE:{
            arithmetic_operation("53",operands);
            break;
        }
        case NOT_CODE:{
            arithmetic_operation("60",operands);
            break;
        }
        case AND_CODE:{
            arithmetic_operation("61",operands);
            break;
        }case OR_CODE:{
            arithmetic_operation("62",operands);
            break;
        }case XOR_CODE:{
            arithmetic_operation("63",operands);
            break;
        }case SHL_CODE:{
            arithmetic_operation("70",operands);
            break;
        }case SHR_CODE:{
            arithmetic_operation("71",operands);
            break;
        }case XCHG_CODE:{
            int reg1, reg2, reg3;
            
            reg1 = 0;
            reg2 = operands[1];
            reg3 = operands[0];

            std::stringstream ss;
            ss << std::hex << reg1 << reg2 << reg3;

            std::string hex_str = ss.str();
            memory_content.push_back(std::make_pair(current_address++, "40"));
            memory_content.push_back(std::make_pair(current_address++, hex_str.substr(0,2)));
            memory_content.push_back(std::make_pair(current_address++, hex_str.substr(2,1) + "0"));
            memory_content.push_back(std::make_pair(current_address++, "00"));
            break;
        }
        default:
            break;
    }

    location_counter+=4;

}


void Assembler::handle_skip(unsigned bytes){          
    for(int i = 0;i<bytes;i++){
        memory_content.push_back(std::make_pair(current_address++, "00"));
        location_counter++;
    }  
}

void Assembler::add_symbol(const symbol& sym){
    sym_table.push_back(sym);
}

void Assembler::arithmetic_operation(const std::string& arithmetic_code, const std::vector<int>& operands){
            int reg1, reg2, reg3;
            
            reg1 = operands[1];
            reg2 = operands[1];
            reg3 = operands[0];

            std::stringstream ss;
            ss << std::hex << reg1 << reg2 << reg3;

            std::string hex_str = ss.str();
            memory_content.push_back(std::make_pair(current_address++, arithmetic_code));
            memory_content.push_back(std::make_pair(current_address++, hex_str.substr(0,2)));
            memory_content.push_back(std::make_pair(current_address++, hex_str.substr(2,1) + "0"));
            memory_content.push_back(std::make_pair(current_address++, "00"));
}

void Assembler::end_last_section(){
    section_tables.back().set_length(current_address - section_tables.back().get_base());
}

void Assembler::handle_sys_regr(std::string& op_code, unsigned reg){
    memory_content.push_back(std::make_pair(current_address++, "90"));
    std::stringstream ss;
    ss << std::hex << reg;

    memory_content.push_back(std::make_pair(current_address++, ss.str() + (op_code == "status" ? "0" : (op_code == "handler" ? "1" : "2"))));

    memory_content.push_back(std::make_pair(current_address++, "00"));
    memory_content.push_back(std::make_pair(current_address++, "00"));
    location_counter+=4;

}

void Assembler::handle_sys_regw(std::string& op_code, unsigned reg){
    memory_content.push_back(std::make_pair(current_address++, "94"));
    std::stringstream ss;
    ss << std::hex << reg;

    memory_content.push_back(std::make_pair(current_address++, (op_code == "status" ? "0" : (op_code == "handler" ? "1" : "2"))+ ss.str()));

    memory_content.push_back(std::make_pair(current_address++, "00"));
    memory_content.push_back(std::make_pair(current_address++, "00"));
    location_counter+=4;

}

bool Assembler::sym_exist(const std::string& sym_name){
    for(const auto& i:sym_table){
        if(sym_name == i.get_name()){
            return true;
        }
    }
    return false;
}

void Assembler::handle_bind_type(bind_type bt, std::string sym_name){
    switch(bt){
        case bind_type::EXT:{
            if(!sym_exist(sym_name)){
            symbol new_sym(sym_table.size(),-1,bind_type::EXT, section_tables.size() ? section_tables.back().get_name(): "UND", sym_name);
            //TODO: ADD TO RELOC TABLE
            add_symbol(new_sym);
            }else{
                for(auto& sym:sym_table){
                    if(sym_name == sym.get_name()){
                        sym.set_bind(bt);
                    }
                }
            }
            break;
        }
        case bind_type::GLO:{
            if(!sym_exist(sym_name)){
                symbol new_sym(sym_table.size(),-1,bind_type::GLO, section_tables.size() ? section_tables.back().get_name(): "UND", sym_name);
                //TODO: ADD TO RELOC TABLE
                add_symbol(new_sym);
            }else{
                for(auto& sym:sym_table){
                    if(sym_name == sym.get_name()){
                        sym.set_bind(bt);
                    }
                }
            }
            break;
        }default:
            break;
    }
}

void Assembler::handle_word(const std::string& sym_name){
    if(!sym_exist(sym_name)){
        symbol new_sym(sym_table.size(),-1,bind_type::LOC, section_tables.size() ? section_tables.back().get_name(): "UND", sym_name);
        //TODO: ADD TO RELOC TABLE
        add_symbol(new_sym);
    }

    flink_table[sym_name].push_back({current_address});
    memory_content.push_back(std::make_pair(current_address++, "00"));
    memory_content.push_back(std::make_pair(current_address++, "00"));
    memory_content.push_back(std::make_pair(current_address++, "00"));
    memory_content.push_back(std::make_pair(current_address++, "00"));
}



void Assembler::handle_word(unsigned literal) {
    for (int i = 0; i < 4; ++i) {
        unsigned byte = (literal >> (i * 8)) & 0xFF;
        std::stringstream ss;
        ss << std::hex << std::setw(2) << std::setfill('0') << byte;
        memory_content.push_back(std::make_pair(current_address++, ss.str()));
    }
}

void Assembler::handle_ascii(std::string& ascii){
    for(const auto& c:ascii){
        unsigned byte = c;
        std::stringstream ss;
        ss << std::hex << std::setw(2) << std::setfill('0') << std::hex<< byte;
        memory_content.push_back(std::make_pair(current_address++, ss.str()));
    }
}


//------------------------------------ Helper functions ---------------------------------------
unsigned Assembler::symbol::get_num() const {
    return _num;
}

int Assembler::symbol::get_value() const {
    return _value;
}



Assembler::bind_type Assembler::symbol::get_bind() const {
    return _bind;
}

std::string Assembler::symbol::get_name() const {
    return _name;
}

void Assembler::symbol::set_num(unsigned num) {
    _num = num;
}

void Assembler::symbol::set_value(unsigned value) {
    _value = value;
}


void Assembler::symbol::set_bind(bind_type bind) {
    _bind = bind;
}

std::string Assembler::symbol::get_section_name() const {
    return _section_name;
}

void Assembler::symbol::set_section_name(const std::string section_name) {
    _section_name = section_name;
}


void Assembler::symbol::set_name(const std::string name) {
    _name = name;
}

unsigned Assembler::section::get_length() const {
    return _length;
}

unsigned Assembler::section::get_base() const {
    return _base;
}

std::string Assembler::section::get_name() const {
    return _name;
}

void Assembler::section::set_length(unsigned length) {
    _length = length;
}


//------------------Writes in file----------------------


void Assembler::write_section_context(){
    ass_output.open("assout.txt", std::ios::app);
    ass_output << "----------Table of sections----------\n";
    
    
    ass_output << std::left << std::setw(15) << "Name:" 
               << std::setw(15) << "Start:" 
               << std::setw(15) << "Size:" << "\n";

    for(const auto& i : section_tables){

        ass_output << std::left << std::setw(15) << i.get_name() 
                   << std::setw(15);
        ass_output << std::hex << i.get_base();
        ass_output << std::setw(15) << std::hex << i.get_length() << "\n";
    }

    ass_output << "-------------------------------------\n";
    ass_output.close();
}

void Assembler::write_memory_content(){
    ass_output.open("assout.txt",std::ios::app);
    ass_output << "------------Section tables-----------\n";
    for(unsigned current_address = 0;current_address < memory_content.size();current_address++){
        if(current_address % 8 == 0){
            if(current_address!=0)ass_output << "\n";
            std::stringstream ss;
            ss << std::hex << current_address << ":";
            ass_output << ss.str();
            ass_output << "\t" << memory_content[current_address].second;
        }else{   
            ass_output << "\t" << memory_content[current_address].second;
        }
    }
    ass_output << "\n-------------------------------------\n";
    ass_output.close();
}


void Assembler::write_symbol_table_context() {
    ass_output.open("assout.txt", std::ios::app);
    ass_output << "----------------Symbol Table----------------\n";
    
    ass_output << std::left << std::setw(10) << "Num:" 
               << std::setw(10) << "Value:" 
               << std::setw(15) << "Bind:" 
               << std::setw(15) << "Section:" 
               << std::setw(15) << "Name:" << "\n";
    for (const auto& sym : sym_table) {
        ass_output << std::left << std::setw(10) << sym.get_num();

        if(sym.get_value()!=-1) ass_output << std::setw(10) << std::hex << sym.get_value();
        else ass_output << std::setw(10) << "UND";

        ass_output << std::setw(15) << (sym.get_bind() == bind_type::LOC ? "LOC" : (sym.get_bind() == bind_type::GLO ? "GLO" : "EXT"))
                   << std::setw(15) << sym.get_section_name()
                   << std::setw(15) << sym.get_name() << "\n";
    }

    ass_output << "---------------------------------------------\n";
    ass_output.close();
}