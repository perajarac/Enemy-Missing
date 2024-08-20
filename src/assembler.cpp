#include "../inc/assembler.hpp"


std::vector<Assembler::section> Assembler::section_tables;
std::vector<Assembler::symbol> Assembler::symbol_tables;
std::vector<std::pair<unsigned, std::string>> Assembler::memory_content;

std::ofstream  Assembler::ass_output;
unsigned Assembler::current_address = 0;


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
            arithmetic_operation("50",operands,current_address);
            break;
        }
        case SUB_CODE:{
            arithmetic_operation("51",operands,current_address);
            break;
        }case MUL_CODE:{
            arithmetic_operation("52",operands,current_address);
            break;
        }case DIV_CODE:{
            arithmetic_operation("53",operands,current_address);
            break;
        }
        case NOT_CODE:{
            arithmetic_operation("60",operands,current_address);
            break;
        }
        case AND_CODE:{
            arithmetic_operation("61",operands,current_address);
            break;
        }case OR_CODE:{
            arithmetic_operation("62",operands,current_address);
            break;
        }case XOR_CODE:{
            arithmetic_operation("63",operands,current_address);
            break;
        }case SHL_CODE:{
            arithmetic_operation("70",operands,current_address);
            break;
        }case SHR_CODE:{
            arithmetic_operation("71",operands,current_address);
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


void Assembler::handle_directive(directive directive, unsigned location_counter){

}

void Assembler::add_symbol(const symbol& sym){
    symbol_tables.push_back(sym);
}

void Assembler::add_memory_context(unsigned address, const std::string& context){

}

void Assembler::write_memory_content(){
    ass_output.open("assout.txt", std::fstream::out);
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

    ass_output.close();
}

void Assembler::arithmetic_operation(const std::string& arithmetic_code, const std::vector<int>& operands, unsigned& current_address){
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

void Assembler::handle_sys_regr(std::string& op_code, int operand){
    if(op_code == "status"){
        
    }else if(op_code == "handler"){

    }else{

    }
}
