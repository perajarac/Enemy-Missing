#include "../inc/assembler.hpp"


bool Assembler::ass_end = false;

std::vector<Assembler::section> Assembler::section_tables;
std::vector<Assembler::symbol> Assembler::sym_table;
std::vector<std::pair<unsigned, std::string>> Assembler::memory_content;

std::unordered_map<std::string, std::vector<Assembler::flink>> Assembler::flink_table_symbols;
std::map<unsigned, int> Assembler::literal_flink;

Assembler::literal_pool Assembler::lit_pool;

std::unordered_map<std::string, std::vector<int>> Assembler::relocation_table;

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
    if(lit_pool.literals.size()>0){
        add_literal_pool_to_memory();
        resolve_literal_flink();
    }
    literal_flink.clear();
    lit_pool.literals.clear();
    lit_pool.set_base(0);
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
            add_symbol(new_sym);
            }else{
                for(auto& sym:sym_table){
                    if(sym_name == sym.get_name()){
                        sym.set_bind(bt);
                    }
                }
            }
            relocation_table[sym_name].push_back(current_address);
            break;
        }
        case bind_type::GLO:{
            if(!sym_exist(sym_name)){
                symbol new_sym(sym_table.size(),-1,bind_type::GLO, section_tables.size() ? section_tables.back().get_name(): "UND", sym_name);
                add_symbol(new_sym);
            }else{
                for(auto& sym:sym_table){
                    if(sym_name == sym.get_name()){
                        sym.set_bind(bt);
                    }
                }
            }
            relocation_table[sym_name].push_back(current_address);
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

    flink_table_symbols[sym_name].push_back({current_address});
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

//------------------------------LOAD INSTRUCTION------------------------------------------
//-----------------------------literal as operand-----------------------------------------

void Assembler::mem_imm_literal(int literal, int reg){
    if(literal < 4096 && literal >= 0){
        memory_content.push_back(std::make_pair(current_address++, "91")); //load imm
        std::stringstream ss;
        ss << std::hex << reg << 0;
        memory_content.push_back(std::make_pair(current_address++, ss.str().substr(0,2)));
        wliteralim(literal);
    }else{
        memory_content.push_back(std::make_pair(current_address++, "92"));
        putlitip(literal,reg);
    }
}

void Assembler::mem_dir_literal(int literal, int reg){
    if(literal < 4096 && literal >= 0){
        memory_content.push_back(std::make_pair(current_address++, "92")); //load imm
        std::stringstream ss;
        ss << std::hex << reg << 0;
        memory_content.push_back(std::make_pair(current_address++, ss.str().substr(0,2)));
        wliteralim(literal);
    }else{
        // ld 0x1234, r4
        // r4 <= mem[pc + offset] --> op code 92
        memory_content.push_back(std::make_pair(current_address++, "92"));
        putlitip(literal,reg);
        // r4 <= mem[r4]  --> op code 92 
        memory_content.push_back(std::make_pair(current_address++, "92"));
        std::stringstream sss;
        sss << std::hex << reg << reg;
        memory_content.push_back(std::make_pair(current_address++, sss.str().substr(0,2)));
        memory_content.push_back(std::make_pair(current_address++, "00"));
        memory_content.push_back(std::make_pair(current_address++, "00"));
    }
}

void Assembler::mem_dir_offset_literal(int reg1, int literal, int reg2){
    if(literal < 4096 && literal >= 0){
        memory_content.push_back(std::make_pair(current_address++, "92")); //load imm
        std::stringstream ss;
        ss << std::hex << reg2 << reg1;
        memory_content.push_back(std::make_pair(current_address++, ss.str().substr(0,2)));
        wliteralim(literal);
    }else{
        std::cout << "\nLiteral can't be written on 12 bits, error in assembling proccess!\n";
        ass_end = true;
    }
}
//-----------------------------register as operand-----------------------------------------
void Assembler::mem_dir_register(int opr_reg, int reg){
    memory_content.push_back(std::make_pair(current_address++, "91")); //load imm
    wregim(opr_reg, reg);
}
void Assembler::mem_ind_register(int opr_reg, int reg){
    memory_content.push_back(std::make_pair(current_address++, "92")); //load imm
    wregim(opr_reg, reg);
}

//------------------------------STORE INSTRUCTION----------------------------------------- st %gpr, operand --> operand <= gpr
//-----------------------------literal as operand-----------------------------------------

void Assembler::st_mem_dir_literal(int reg, int literal){
    if(literal < 4096 && literal >= 0){ 
        memory_content.push_back(std::make_pair(current_address++, "80"));
        memory_content.push_back(std::make_pair(current_address++, "00"));
        int temp = 0b111100000000;
        int upper = literal & temp;
        literal = literal & (~temp);
        upper = upper >> 8;
        std::stringstream sss;
        sss << std::hex  << reg  << upper  
            << std::setw(2) << std::setfill('0') << literal;           
        std::string first_part = sss.str().substr(0, 2); 
        std::string second_part = sss.str().substr(2, 2); 

        memory_content.push_back(std::make_pair(current_address++, first_part));
        memory_content.push_back(std::make_pair(current_address++, second_part));
    }else{
        memory_content.push_back(std::make_pair(current_address++, "82"));
        memory_content.push_back(std::make_pair(current_address++, "0f"));
        literal = (literal << 8) | reg;
        literal_flink[current_address] = lit_pool.return_index_of_literal(literal);
        memory_content.push_back(std::make_pair(current_address++, "00"));
        memory_content.push_back(std::make_pair(current_address++, "00"));
    }
}

void Assembler::st_mem_dir_reg(int reg1, int reg2){
    memory_content.push_back(std::make_pair(current_address++, "82"));
    std::stringstream ss;
    ss << std::hex << std::setw(2) << std::setfill('0') << reg1; 
    
    std::string temp = ss.str().substr(0, 2);
    memory_content.push_back(std::make_pair(current_address++, temp));

    std::string first_part = "00";
    first_part[0] = std::to_string(reg2)[0];

    memory_content.push_back(std::make_pair(current_address++, first_part));
    memory_content.push_back(std::make_pair(current_address++, "00"));
}


void Assembler::st_mem_dir_offset_literal(int reg1, int literal, int reg2){
    if(literal < 4096 && literal >= 0){
        memory_content.push_back(std::make_pair(current_address++, "82"));
        std::stringstream ss;
        ss << std::hex << std::setw(2) << std::setfill('0') << reg1; 
        
        std::string temp = ss.str().substr(0, 2);
        memory_content.push_back(std::make_pair(current_address++, temp));

        std::string first_part = "00";
        first_part[0] = std::to_string(reg2)[0];
        ss.str("");
        ss.clear();
        ss << std::hex << std::setw(2) << std::setfill('0') << ((literal&0xf00)>>8); 
        first_part[1] = ss.str()[1];

        std::stringstream sss;
        sss << std::hex << std::setw(2) << std::setfill('0') << (literal & 0xff);

        memory_content.push_back(std::make_pair(current_address++, first_part));
        memory_content.push_back(std::make_pair(current_address++, sss.str()));
    }else{
        std::cout << "\nLiteral can't be written on 12 bits, error in assembling proccess!\n";
        ass_end = true;
    }
}

//-----------------------------symbol as operand-----------------------------------------


void Assembler::handle_label(std::string ident){
    if(!section_tables.size()){
        std::cout << "Error in assembling proces, labels can't be written outside sections\n";
        ass_end = true;
        return;
    }
    int index = -1;
    for(int i = 0;i<sym_table.size();i++){
        if(ident == sym_table[i].get_name()){
            index = i;
        }
    }

    if(index!=-1 && sym_table[index].get_section_name() == "UND"){
        sym_table[index].set_section_name(section_tables.back().get_name());
    }else if(!sym_exist(ident)){
        symbol new_sym(sym_table.size(),-1,bind_type::LOC, section_tables.back().get_name(), ident);
        add_symbol(new_sym);
    }else{
        std::cout << "Error, label can't be defined twice\n";
        ass_end = true;
    }
}


void Assembler::mem_imm_symbol(std::string ident, int reg){}
void Assembler::mem_dir_symbol(std::string ident, int reg){}





















void Assembler::resolve_literal_flink(){
    std::unordered_map<int,int> processed;
    for (const auto& [memory_address, inde] : literal_flink) {
        auto it = std::find_if(
            memory_content.begin(), 
            memory_content.end(), 
            [memory_address](const std::pair<unsigned, std::string>& element) {
                return element.first == memory_address;
            }
        );

        if (it != memory_content.end()) {
            int index = inde;
            int temp  = (lit_pool.literals[index] & 0xf);
            int key = lit_pool.literals[index] >> 8;

            // Use std::find_if to check if the key is in the processed map
            auto processed_it = std::find_if(
                processed.begin(), 
                processed.end(), 
                [key](const std::pair<const int, int>& element) {
                    return element.first == key;
                }
            );
            if (processed_it == processed.end()) {
                processed[key] = index;
            } else {
                index = processed_it->second;
            }
            unsigned pomeraj = lit_pool.get_base() + index * 4 - memory_address + 2;

            //for store and jumps not just literals are on lower 2 bytes so i added gpr[c] in literal temp vector and i undo it here
            if(temp!=0) lit_pool.literals[index] = lit_pool.literals[index] >> 8;


            unsigned low_byte = pomeraj & 0xFF;         
            unsigned high_nibble = ((pomeraj) & 0xF00) >> 8;

            std::stringstream ss;
            std::stringstream sss;

            sss << std::hex << temp;
            ss << std::hex << (high_nibble);
            it->second[1] = ss.str()[0];
            it->second[0] = sss.str()[0];

            ++it;
            if (it != memory_content.end()) {
                std::stringstream ss_low;
                ss_low << std::setw(2) << std::setfill('0') << std::hex << low_byte;
                it->second = ss_low.str();
            }
        }
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


void Assembler::add_literal_pool_to_memory(){
    lit_pool.set_base(current_address);
    std::unordered_set<decltype(lit_pool.literals)::value_type> processed;

    for (const auto& i : lit_pool.literals) {
        if (processed.insert(i>>8).second) {
            // If insertion was successful, the item is being handled for the first time
            handle_word(i>>8);
        }
    }
}

//used in load to put literal value in lower 2 bytes
void Assembler::wliteralim(int literal){
    int temp = 0b111100000000;
    int upper = literal & temp;
    literal = literal & (~temp);
    upper = upper >> 8;
    std::stringstream sss;
    sss << std::hex << std::setw(2) << std::setfill('0') << upper  
        << std::setw(2) << std::setfill('0') << literal;           
    std::string first_part = sss.str().substr(0, 2); 
    std::string second_part = sss.str().substr(2, 2); 

    memory_content.push_back(std::make_pair(current_address++, first_part));
    memory_content.push_back(std::make_pair(current_address++, second_part));
}

//used in load functions to fill 2nd byte of instruction
void Assembler::wregim(int opr_reg, int reg){
    std::stringstream ss;
    ss << std::hex << reg << opr_reg;
    memory_content.push_back(std::make_pair(current_address++, ss.str().substr(0,2)));
    memory_content.push_back(std::make_pair(current_address++, "00"));
    memory_content.push_back(std::make_pair(current_address++, "00"));
}

//put literal in literal pool and reserve place for offset
void Assembler::putlitip(int literal, int reg){
    std::stringstream ss;
    ss << std::hex << reg << 15;
    memory_content.push_back(std::make_pair(current_address++, ss.str().substr(0,2)));
    literal_flink[current_address] = lit_pool.return_index_of_literal(literal << 8);
    memory_content.push_back(std::make_pair(current_address++, "00"));
    memory_content.push_back(std::make_pair(current_address++, "00"));
}

//temp funtion used in store functions. fills lower 2 bytes of instruction with registar value that is being stored and literal address
void Assembler::wlitims(int literal, int reg){
    int temp = 0b111100000000;
    int upper = literal & temp;
    literal = literal & (~temp);
    upper = upper >> 8;
    std::stringstream sss;
    sss << std::hex  << reg  << upper  
        << std::setw(2) << std::setfill('0') << literal;           
    std::string first_part = sss.str().substr(0, 2); 
    std::string second_part = sss.str().substr(2, 2); 

    memory_content.push_back(std::make_pair(current_address++, first_part));
    memory_content.push_back(std::make_pair(current_address++, second_part));
}