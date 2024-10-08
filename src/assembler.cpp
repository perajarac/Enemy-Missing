#include "../inc/assembler.hpp"


std::string Assembler::output_file_txt;
std::string Assembler::output_file_obj;
bool Assembler::ass_end = false;

int Assembler::lit_pool_base_address = 0;
std::map<int, int> Assembler::ascii_map;
std::vector<section> Assembler::section_tables;
std::vector<symbol> Assembler::sym_table;
std::vector<std::pair<int, std::string>> Assembler::memory_content;

std::unordered_map<std::string, std::vector<int>> Assembler::symbols_flink;
std::unordered_map<std::string, std::vector<int>> Assembler::symbols_jump_flink;
std::map<int, int> Assembler::literal_flink;

Assembler::literal_pool Assembler::lit_pool;

std::ofstream  Assembler::ass_output;
std::ofstream  Assembler::ass_obj_output;
int Assembler::current_address = 0;

void Assembler::set_output(std::string output){
    output_file_obj = output;
    output_file_txt = output;

    size_t dot_pos = output_file_txt.rfind(".o");
    output_file_txt.replace(dot_pos, 2, ".txt");
}

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
            std::pair<unsigned, std::string> to_add = std::make_pair(current_address++, "10");
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


}


void Assembler::handle_skip(unsigned bytes){
    ascii_map[current_address] = bytes;          
    for(int i = 0;i<bytes;i++){
        memory_content.push_back(std::make_pair(current_address++, "00"));
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

void Assembler::mk_iret(){
    pop(0, true);
    pop(15,false);
}

void Assembler::mk_call(std::string ident){
    memory_content.push_back({current_address++, "21"});
    std::stringstream ss;
    ss << std::hex << 0 << 15;
    memory_content.push_back(std::make_pair(current_address++, ss.str().substr(0,2)));


    if(!sym_exist(ident)){
        symbol new_sym(sym_table.size(),-1,bind_type::LOC, "UND", ident);
        add_symbol(new_sym);
    }

    symbols_jump_flink[ident].push_back(current_address);
    memory_content.push_back(std::make_pair(current_address++, "00"));
    memory_content.push_back(std::make_pair(current_address++, "00"));

}

void Assembler::mk_call(long literal){
    if(literal>=0 && literal < 4096){
        memory_content.push_back({current_address++, "20"});
        memory_content.push_back({current_address++, "00"});
        wliteralim(literal);
    }else{
        memory_content.push_back(std::make_pair(current_address++, "21"));
        putlitip(literal,0);
    }
}

void Assembler::jump_sym(instruction ins, int gpr1, int gpr2, std::string ident){

    if(!sym_exist(ident)){
        symbol new_sym(sym_table.size(),-1,bind_type::LOC, "UND", ident);
        add_symbol(new_sym);
    }
    switch(ins){
        case JMP_CODE:{
            memory_content.push_back({current_address++, "38"});
            break;
        }
        case BEQ_CODE:{
            memory_content.push_back({current_address++, "39"});
            break;
        }case BNE_CODE:{
            memory_content.push_back({current_address++, "3a"});
            break;
        }case BGT_CODE:{
            memory_content.push_back({current_address++, "3b"});
            break;
        }
    }
    std::stringstream ss;
    ss << std::hex << 15 << gpr1;
    memory_content.push_back({current_address++, ss.str().substr(0,2)});
    ss.str("");
    ss.clear();

    ss << std::hex << gpr2 << 0;
    symbols_jump_flink[ident].push_back(current_address);
    memory_content.push_back({current_address++, ss.str().substr(0,2)});
    memory_content.push_back({current_address++, "00"});
    
}

void Assembler::jump_lit(instruction ins, int gpr1, int gpr2, long literal){
    if(literal >= 0 && literal < 4096){
        switch(ins){
            case JMP_CODE:{
                memory_content.push_back({current_address++, "30"});
                break;
            }
            case BEQ_CODE:{
                memory_content.push_back({current_address++, "31"});
                break;
            }case BNE_CODE:{
                memory_content.push_back({current_address++, "32"});
                break;
            }case BGT_CODE:{
                memory_content.push_back({current_address++, "33"});
                break;
            }
        }
        std::stringstream ss;
        ss << std::hex << 0 << gpr1;
        memory_content.push_back({current_address++, ss.str().substr(0,2)});
        ss.str("");
        ss.clear();
        ss << std::hex << gpr2 << ((literal>>8)&0xf);
        memory_content.push_back({current_address++, ss.str().substr(0,2)});
        ss.str("");
        ss.clear();
        ss << std::hex << ((literal>>4)&0xf) << ((literal)&0xf);
        memory_content.push_back({current_address++, ss.str().substr(0,2)});
    }else{
        switch(ins){
            case JMP_CODE:{
                memory_content.push_back({current_address++, "38"});
                break;
            }
            case BEQ_CODE:{
                memory_content.push_back({current_address++, "39"});
                break;
            }case BNE_CODE:{
                memory_content.push_back({current_address++, "3a"});
                break;
            }case BGT_CODE:{
                memory_content.push_back({current_address++, "3b"});
                break;
            }
        }
        std::stringstream ss;
        ss << std::hex << 15 << gpr1;
        memory_content.push_back({current_address++, ss.str().substr(0,2)});
        literal = (literal << 8) | gpr2;
        literal_flink[current_address] = lit_pool.return_index_of_literal(literal & mask);
        memory_content.push_back(std::make_pair(current_address++, "00"));
        memory_content.push_back(std::make_pair(current_address++, "00"));

    }
}

void Assembler::resolve_jump(){
    auto section = section_tables.back();
    std::vector<std::string>tbd;
    for(auto sym_flink: symbols_jump_flink){ //for every symbol in flink
        symbol sym = sym_table[sym_index(sym_flink.first)];
        if(sym.get_name() != sym_flink.first || sym.get_section_name() != section.get_name())continue;//check if it is defined withing current section
        for(auto address:sym_flink.second){ //if it is it patches memory content of jmp instruction
            for(auto data = memory_content.begin(); data != memory_content.end();data++){
                if(data->first != address) continue;
                int pomeraj = ((sym.get_value()-section.get_base())-address) + 2; //with offset to that symbol
                if (pomeraj < 0) {
                    pomeraj = (pomeraj & 0xfff); // Keep only the 12 lowest bits (two's complement)

                }
                
                std::stringstream ss;
                ss << std::hex <<((pomeraj>>8)&0xf);
                data->second[1] = ss.str()[0];
                ss.str("");
                ss.clear();
                ss << std::hex << ((pomeraj>>4)&0xf) << ((pomeraj)&0xf);
                data++; 
                if((data-3)->second[0] == '3'){ //for jump ins
                    char op_code = (data-3)->second[1];
                    int num = (op_code >= 'a') ? (op_code - 'a' + 10) : (op_code - '0');  // Convert hex char to int
                    (data-3)->second[1] = num - 8 + '0'; //change op code to be without mem[]
                    
                }else{
                    (data-3)->second[1] = '0'; //for call ins change op code to be without mem[]
                }

                if(data!=memory_content.end())data->second = ss.str();
            }
        }
        tbd.push_back(sym.get_name()); //add entry to vector that holds name of keys that should be deleted
    }
    for(auto key:tbd){
        symbols_jump_flink.erase(key);//delete all entries with resolved symbols  
    }

    for(auto sym: symbols_jump_flink){
        symbols_flink[sym.first].insert(symbols_flink[sym.first].end(), sym.second.begin(), sym.second.end()); //add unresolved to sym flink
    }
}

void Assembler::end_last_section(){
    if(lit_pool.literals.size()>0){
        add_literal_pool_to_memory();
        resolve_literal_flink();
    }
    resolve_jump();
    resovle_symbol_flink();
    symbols_flink.clear();
    literal_flink.clear();
    symbols_jump_flink.clear();
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
}

void Assembler::handle_sys_regw(std::string& op_code, unsigned reg){
    memory_content.push_back(std::make_pair(current_address++, "94"));
    std::stringstream ss;
    ss << std::hex << reg;

    memory_content.push_back(std::make_pair(current_address++, (op_code == "status" ? "0" : (op_code == "handler" ? "1" : "2"))+ ss.str()));

    memory_content.push_back(std::make_pair(current_address++, "00"));
    memory_content.push_back(std::make_pair(current_address++, "00"));


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
            symbol new_sym(sym_table.size(),-1,bind_type::EXT, "UND", sym_name);
            add_symbol(new_sym);
            }else{
                int index = sym_index(sym_name);
                sym_table[index].set_bind(bt);    
            }
            break;
        }
        case bind_type::GLO:{
            int index = sym_index(sym_name);
            if(!sym_exist(sym_name)){
                symbol new_sym(sym_table.size(),-1,bind_type::GLO, "UND", sym_name);
                add_symbol(new_sym);
            }else{
                int index = sym_index(sym_name);
                sym_table[index].set_bind(bt);    
            }
            break;
        }default:
            break;
    }
}

void Assembler::handle_word(const std::string& sym_name){
    if(!sym_exist(sym_name)){
        symbol new_sym(sym_table.size(),-1,bind_type::LOC, "UND", sym_name);
        add_symbol(new_sym);
    }
    symbol curr_sym = sym_table[sym_index(sym_name)];
    section& current_section = section_tables.back();
    bool ternar = curr_sym.get_bind() == LOC;
    int offset = current_address-current_section.get_base();
    current_section.relocation_table.push_back({offset, curr_sym.get_name(), (ternar ? curr_sym.get_value():0), (ternar? true:false)}); //put symbol in reloc table of section
    memory_content.push_back(std::make_pair(current_address++, "00"));
    memory_content.push_back(std::make_pair(current_address++, "00"));
    memory_content.push_back(std::make_pair(current_address++, "00"));
    memory_content.push_back(std::make_pair(current_address++, "00"));

}



void Assembler::handle_word(long literal) {
    for (int i = 3; i >= 0; --i) {  // Start from the most significant byte
        unsigned byte = (literal >> (i * 8)) & 0xFF;
        std::stringstream ss;
        ss << std::hex << std::setw(2) << std::setfill('0') << byte;
        memory_content.push_back(std::make_pair(current_address++, ss.str()));
    }
}

void Assembler::handle_ascii(std::string& ascii){
    ascii_map[current_address] = ascii.size();
    for(const auto& c:ascii){
        unsigned byte = c;
        std::stringstream ss;
        ss << std::hex << std::setw(2) << std::setfill('0') << std::hex<< byte;
        memory_content.push_back(std::make_pair(current_address++, ss.str()));
    }
}

void Assembler::pop(int reg, bool csr){
    if(csr){
        memory_content.push_back(std::make_pair(current_address++, "97"));
    }else{
        memory_content.push_back(std::make_pair(current_address++, "93"));
    }
    std::stringstream ss;
    ss << std::hex << reg << 14;
    memory_content.push_back(std::make_pair(current_address++, ss.str().substr(0,2)));
    memory_content.push_back(std::make_pair(current_address++, "00"));
    memory_content.push_back(std::make_pair(current_address++, "04"));
}

void Assembler::push(int reg){
    memory_content.push_back(std::make_pair(current_address++, "81"));
    std::stringstream ss;
    ss << std::hex << 14 << 0;
    memory_content.push_back(std::make_pair(current_address++, ss.str().substr(0,2)));
    ss.str("");
    ss.clear();
    ss << std::hex << reg <<((-4>>8)&0xf);
    memory_content.push_back(std::make_pair(current_address++, ss.str().substr(0,2)));
    ss.str("");
    ss.clear();
    ss << std::hex << ((-4>>4)&0xf) << ((-4)&0xf);
    memory_content.push_back(std::make_pair(current_address++, ss.str().substr(0,2))); 
}

//------------------------------LOAD INSTRUCTION------------------------------------------
//-----------------------------literal as operand-----------------------------------------

void Assembler::mem_imm_literal(long literal, int reg){
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

void Assembler::mem_dir_literal(long literal, int reg){
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

void Assembler::mem_dir_offset_literal(int reg1, long literal, int reg2){
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


//-----------------------------symbol as operand-----------------------------------------
void Assembler::mem_imm_symbol(std::string ident, int reg){

    if(!sym_exist(ident)){
        symbol new_sym(sym_table.size(),-1,bind_type::LOC, "UND", ident);
        add_symbol(new_sym);
    }
    memory_content.push_back({current_address++, "92"});
    std::stringstream ss;
    ss << std::hex << reg << 15;
    memory_content.push_back(std::make_pair(current_address++, ss.str().substr(0,2)));
    symbols_flink[ident].push_back(current_address);
    memory_content.push_back(std::make_pair(current_address++, "00"));
    memory_content.push_back(std::make_pair(current_address++, "00"));

}

void Assembler::mem_dir_symbol(std::string ident, int reg){

    if(!sym_exist(ident)){
        symbol new_sym(sym_table.size(),-1,bind_type::LOC, "UND", ident);
        add_symbol(new_sym);
    }

    memory_content.push_back({current_address++, "92"});
    std::stringstream ss;
    ss << std::hex << reg << 15;
    memory_content.push_back(std::make_pair(current_address++, ss.str().substr(0,2)));
    symbols_flink[ident].push_back(current_address);
    memory_content.push_back(std::make_pair(current_address++, "00"));
    memory_content.push_back(std::make_pair(current_address++, "00"));


    memory_content.push_back(std::make_pair(current_address++, "92"));
    std::stringstream sss;
    sss << std::hex << reg << reg;
    memory_content.push_back(std::make_pair(current_address++, sss.str().substr(0,2)));
    memory_content.push_back(std::make_pair(current_address++, "00"));
    memory_content.push_back(std::make_pair(current_address++, "00"));

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
        literal = ((literal << 8) | reg) & mask;
        literal_flink[current_address] = lit_pool.return_index_of_literal(literal);
        memory_content.push_back(std::make_pair(current_address++, "00"));
        memory_content.push_back(std::make_pair(current_address++, "00"));
    }
}

void Assembler::st_mem_dir_reg(int reg1, int reg2){
    memory_content.push_back(std::make_pair(current_address++, "80"));
    std::stringstream ss;
    ss << std::hex << std::setw(2) << std::setfill('0') << reg1; 
    
    std::string temp = ss.str().substr(0, 2);
    memory_content.push_back(std::make_pair(current_address++, temp));

    std::string first_part = "00";
    first_part[0] = std::to_string(reg2)[0];

    memory_content.push_back(std::make_pair(current_address++, first_part));
    memory_content.push_back(std::make_pair(current_address++, "00"));
}


void Assembler::st_mem_dir_offset_literal(int reg1, long literal, int reg2){
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

void Assembler::st_mem_dir_symbol(std::string ident, int reg){
    if(!sym_exist(ident)){
        symbol new_sym(sym_table.size(),-1,bind_type::LOC, "UND", ident);
        add_symbol(new_sym);
    }

    memory_content.push_back(std::make_pair(current_address++, "82"));
    memory_content.push_back(std::make_pair(current_address++, "0f"));

    int combined = (reg << 4) | 0x0;
    std::stringstream ss;

    ss << std::hex << std::setw(2) << std::setfill('0') << combined;
    memory_content.push_back(std::make_pair(current_address, ss.str()));
    
    symbols_flink[ident].push_back(current_address++);
    memory_content.push_back(std::make_pair(current_address++, "00"));
}

//-----------------------------symbol as operand-----------------------------------------


void Assembler::handle_label(std::string ident){
    if(!section_tables.size()){
        std::cout << "Error in assembling proces, labels can't be written outside sections\n";
        ass_end = true;
        return;
    }

    int index = sym_index(ident);

    if(index!=-1 && sym_table[index].get_bind() == bind_type::EXT){
        std:: cout << "Error, cant define extern symbol";
        ass_end = true;
        return;
    }else if(index!=-1 && sym_table[index].get_value() != -1){
        std::cout << "Error, label can't be defined twice\n";
        ass_end = true;
        return;
    }else if(index!=-1 && sym_table[index].get_section_name() == "UND" ){
        sym_table[index].set_section_name(section_tables.back().get_name()); //if sym is global but undefined
    }else if(!sym_exist(ident)){
        symbol new_sym(sym_table.size(),-1,bind_type::LOC, section_tables.back().get_name(), ident); //if symbol doesnt exists
        add_symbol(new_sym);
        index = sym_index(ident);
    }
    sym_table[index].set_value(current_address - section_tables.back().get_base()); //set value or global or local symbol relative from section begin
}

void Assembler::resovle_symbol_flink(){
    for(auto& sym:symbols_flink){ //goes for every symbol
        for(auto address:sym.second){ //for every address that is coresponding with that symbol
            for (auto it = memory_content.begin(); it != memory_content.end(); ++it) { //searching memmory to find one of the addresses that coresponds with symbol
                if (it->first == address) { //if search is success adds offset to that symbol in literal pool
                    int pomeraj = current_address - address + 2;

                    int low_byte = pomeraj & 0xFF;         
                    int high_nibble = ((pomeraj) & 0xF00) >> 8;

                    std::stringstream ss;
                    ss << std::hex << (high_nibble);
                    it->second[1] = ss.str()[0];

                    ++it;
                    if (it != memory_content.end()) {
                        std::stringstream ss_low;
                        ss_low << std::setw(2) << std::setfill('0') << std::hex << low_byte;
                        it->second = ss_low.str();
                    }

                    symbol curr_sym = sym_table[sym_index(sym.first)];
                    section& current_section = section_tables.back();
                    bool ternar = curr_sym.get_bind() == LOC;
                    int offset = current_address-current_section.get_base();
                    current_section.relocation_table.push_back({offset, curr_sym.get_name(), (ternar ? curr_sym.get_value():0), (ternar? true:false)}); //put symbol in reloc table of section
                    if(section_tables.back().get_lit_pool_base() == 0) section_tables.back().set_lit_pool_base(current_address);
                    memory_content.push_back(std::make_pair(current_address++, "00"));
                    memory_content.push_back(std::make_pair(current_address++, "00"));
                    memory_content.push_back(std::make_pair(current_address++, "00"));
                    memory_content.push_back(std::make_pair(current_address++, "00"));
                    break;
                        
                }
            }
        }

    }
}

void Assembler::resolve_literal_flink(){
    std::unordered_map<long,long> processed;
    for (const auto& [memory_address, inde] : literal_flink) {
        auto it = std::find_if(
            memory_content.begin(), 
            memory_content.end(), 
            [memory_address](const std::pair<unsigned, std::string>& element) {
                return element.first == memory_address;
            }
        );

        if (it != memory_content.end()) {
            long index = inde;
            long temp  = (lit_pool.literals[index] & 0xf);
            long key = lit_pool.literals[index] >> 8;

            // Use std::find_if to check if the key is in the processed map
            auto processed_it = std::find_if(
                processed.begin(), 
                processed.end(), 
                [key](const std::pair<const long, long>& element) {
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

int Assembler::sym_index(const std::string& ident){
    int index = -1;
    for(int i = 0;i<sym_table.size();i++){
        if(ident == sym_table[i].get_name()){
            index = i;
        }
    }
    return index;
}

//------------------Writes in file----------------------


void Assembler::write_section_context(){
    ass_output.open(output_file_txt, std::ios::app);
    ass_output << "----------Table of sections----------\n";
    
    
    ass_output << std::left << std::setw(15) << "Name:" 
               << std::setw(15) << "Start:" 
               << std::setw(15) << "Size:" 
               << std::setw(15) << "Lit pool adrr:" << "\n";

    for(const auto& i : section_tables){

        ass_output << std::left << std::setw(15) << i.get_name() 
                   << std::setw(15);
        ass_output << std::hex << i.get_base();
        ass_output << std::setw(15) << std::hex << i.get_length();
        ass_output << std::setw(15) << std::hex << i.get_lit_pool_base() << "\n";
    }

    ass_output << "-------------------------------------\n";
    ass_output.close();
}

void Assembler::write_memory_content(){
    std::map<int,int> lit_pool_base_addreses;
    for(auto s:section_tables){ 
        if(s.get_lit_pool_base()!=0 && s.get_length()!=0) lit_pool_base_addreses[s.get_lit_pool_base()] = s.get_length() - s.get_lit_pool_base(); //map of start of lit_pool and its length
    }
    auto lpba_it = lit_pool_base_addreses.begin();
    int n = memory_content.size();
    ass_output.open(output_file_txt,std::ios::app);
    ass_output << "------------Section tables-----------\n";
    for(int current_address = 0;current_address < n;){

        if(lpba_it != lit_pool_base_addreses.end() && lpba_it->second != 0){ //prints literal pool
            if(current_address >= lpba_it->first){
                for(int i = 0; i<lpba_it->second;i++){
                    if(current_address % 8 == 0){
                        ass_output << "\n";
                        std::stringstream ss;
                        ss << std::hex << current_address << ":";
                        ass_output << ss.str();
                    }               
                    ass_output << "\t" << memory_content[current_address++].second;
                }
                lpba_it++;
                continue;
            }
        }

        auto it = ascii_map.find(current_address);//prints ascii or skip properly
        if(it != ascii_map.end()){
            for(int i = 0; i<it->second;i++){
                if(current_address % 8 == 0){
                    ass_output << "\n";
                    std::stringstream ss;
                    ss << std::hex << current_address << ":";
                    ass_output << ss.str();
                }               
                ass_output << "\t" << memory_content[current_address++].second;
            }
            continue;
        }

        if(current_address % 8 == 0){
            if(current_address!=0)ass_output << "\n";
            std::stringstream ss;
            ss << std::hex << current_address << ":";
            ass_output << ss.str();
        }
        ass_output << "\t" << memory_content[current_address+3].second; //prints instruction
        ass_output << "\t" << memory_content[current_address+2].second;
        ass_output << "\t" << memory_content[current_address+1].second;
        ass_output << "\t" << memory_content[current_address].second;
        current_address += 4;
    }

    ass_output << "\n-------------------------------------\n";
    ass_output.close();
}



void Assembler::write_symbol_table_context() {
    ass_output.open(output_file_txt, std::ios::app);
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

void Assembler::write_realoc(){
    ass_output.open(output_file_txt, std::ios::app);
    ass_output << "----------------Reloc Table----------------\n";

    ass_output << std::left << std::setw(20) << "Section:" << std::setw(20) << "Symbol:" 
            << std::setw(10) << "Offset:" << std::setw(10) << "Addend:" <<  "\n";

    for (const auto& section : section_tables) {
        ass_output << std::left << std::setw(20) << section.get_name() << "\n"; // New line for each section

        for (const auto& reloc_node : section.relocation_table) {
            ass_output << std::setw(20) << ""  // Empty column for section name to align
                    << std::setw(20) << reloc_node.symbol_name
                    << std::setw(20) << reloc_node.offset
                    << std::setw(20) << reloc_node.addend;

            
            ass_output << "\n";  // New line for each symbol
        }
    }

    ass_output << "---------------------------------------------\n";
    ass_output.close();

}

void Assembler::write_object_file(){
    ass_obj_output.open(output_file_obj, std::ios::binary | std::ios::out);

    //writes sections content in obj file
    int section_table_size = section_tables.size();
    ass_obj_output.write((char*)(&section_table_size), sizeof(section_table_size));
    for(const auto& section : section_tables){
        std::string sec_name = section.get_name();
        int name_len = sec_name.size();
        ass_obj_output.write((char*)&name_len, sizeof(name_len));
        for(int j = 0; j < name_len; j++) {
            char c = sec_name[j];
            ass_obj_output.write((char*)(&c), sizeof(c));
        }
        ass_obj_output.write((char*)&section._base, sizeof(section._base));
        ass_obj_output.write((char*)&section._length, sizeof(section._length));
        ass_obj_output.write((char*)&section._lit_pool_base, sizeof(section._lit_pool_base));
    // Write Relocation Table of section
        int reloc_table_size = section.relocation_table.size();
        ass_obj_output.write((char*)(&reloc_table_size), sizeof(reloc_table_size));
        for(const auto& relocation : section.relocation_table){
            std::string sym_name = relocation.symbol_name;
            int name_len = sym_name.size();
            ass_obj_output.write((char*)&name_len, sizeof(name_len));
            for(int j = 0; j < name_len; j++) {
                char c = sym_name[j];
                ass_obj_output.write((char*)(&c), sizeof(c));
            }
            int reloc_offset = relocation.offset;
            ass_obj_output.write((char*)&reloc_offset, sizeof(reloc_offset));
            int reloc_addend = relocation.addend;
            ass_obj_output.write((char*)&reloc_addend, sizeof(reloc_addend));
            bool reloc_is_section = relocation.is_section;
            ass_obj_output.write((char*)&reloc_is_section, sizeof(reloc_is_section));
            
        }   
    }
    
    // Write Symbol Table
    int symbol_table_size = sym_table.size();
    ass_obj_output.write((char*)(&symbol_table_size), sizeof(symbol_table_size));
    for(const auto& symbol : sym_table){
        std::string sym_name = symbol.get_name();
        int name_len = sym_name.size();
        ass_obj_output.write((char*)&name_len, sizeof(name_len));
        for(int j = 0; j < name_len; j++) {
            char c = sym_name[j];
            ass_obj_output.write((char*)(&c), sizeof(c));
        }
        ass_obj_output.write((char*)&symbol._value, sizeof(symbol._value));
        ass_obj_output.write((char*)&symbol._bind, sizeof(symbol._bind));

        std::string section_name = symbol.get_section_name();
        name_len = section_name.size();
        ass_obj_output.write((char*)&name_len, sizeof(name_len));
        for(int j = 0; j < name_len; j++) {
            char c = section_name[j];
            ass_obj_output.write((char*)(&c), sizeof(c));
        }
    }

    // Write mem content
    int memory_content_size = memory_content.size();
    ass_obj_output.write((char*)(&memory_content_size), sizeof(memory_content_size));
    for(const auto& [address, content] : memory_content){
        for(int j = 0; j < 2; j++) {
            char c = content[j];
            ass_obj_output.write((char*)(&c), sizeof(c));
        }
    }

    ass_obj_output.close();
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
void Assembler::putlitip(long literal, int reg){
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


void Assembler::local_sym_errors(){
    for(auto& sym: sym_table){
        if((sym.get_bind() == bind_type::LOC) && sym.get_section_name() == "UND"){
            std::cout << "Error, symbol " << sym.get_name() << " is not defined\n";
            ass_end = true;
        }
        if((sym.get_bind() == bind_type::GLO) && sym.get_value() == -1){
            sym.set_bind(bind_type::EXT);
        }
    }
}

void Assembler::resolve_local_sym_reloc(){ //we want to change sym name for section name and to check if undefined symbols have definition
    for(section& sec : section_tables){
    for(reloc_node& rel_node:sec.relocation_table){
        if(!rel_node.is_section)continue; //if symbol is not local skip
        std::string sym_name = rel_node.symbol_name;
        symbol sym = sym_table[sym_index(sym_name)];
        if(sym.get_value() == -1){
            std::cout << "Error, symbol " << sym.get_name() << " is not defined\n";
            exit(-1);
        }
        rel_node.symbol_name = sec.get_name();
        rel_node.addend = sym.get_value();
    }
}
}