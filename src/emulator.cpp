#include "../inc/emulator.hpp"


std::vector<int> Emulator::gprs(15,0);
std::vector<int> Emulator::csrs(3,0);
int& Emulator::sp = gprs[14];
int& Emulator::pc = gprs[15];
std::vector<section> Emulator::sections;
bool Emulator::emulating = false;

std::map<int,char> Emulator::memory;
std::string Emulator::obj_hex;

void Emulator::read_obj(){
    if(obj_hex == ""){
        std::cerr << "Error, no input file\n";
        exit(-1);
    }
    std::ifstream obj_file(obj_hex, std::ios::binary);
    //reading section table content of current file
    int num_of_sec = 0; 
    obj_file.read(reinterpret_cast<char*>(&num_of_sec), sizeof(int));
    for(int i = 0; i < num_of_sec; i++){
        section temp_sec;

        obj_file.read(reinterpret_cast<char*>(&temp_sec._base), sizeof(int));
        obj_file.read(reinterpret_cast<char*>(&temp_sec._length), sizeof(int));
        
        int sec_mem_size = 0;  
        obj_file.read(reinterpret_cast<char*>(&sec_mem_size), sizeof(int));
        std::vector<std::pair<int, std::string>> memory_content;
        for(int i = 0; i < sec_mem_size; i++){
            std::string byte(2, '\0');
            obj_file.read(&byte[0],2);
            memory_content.push_back({i,byte});
        }

        temp_sec.memory_content = memory_content;
        sections.push_back(temp_sec);
    }
}

void Emulator::map_memory(){
    auto hex_string_to_byte = [](const std::string& hex_string) -> unsigned char {
        unsigned int byte;
        std::stringstream ss;
        ss << std::hex << hex_string;
        ss >> byte;
        return static_cast<unsigned char>(byte);
    };

    for (const section& sec : sections) {
        int base = sec.get_base();  
        for (const auto& mem_pair : sec.memory_content) {
            int offset = mem_pair.first;
            unsigned char byte_value = hex_string_to_byte(mem_pair.second);
            int dest_address = base + offset;
            memory[dest_address] = byte_value;
        }
    }
}

void Emulator::lae_ins(){
    op_codes op_code;
    int a,b,c,d;
    auto it = memory.find(pc);
    if (it == memory.end()) {
        std::cout << "PC fault, nothing on that address" << std::endl;
        return;
    } 
    uint instruction = memory[pc];
    op_code = (op_codes)(instruction >> 24);
    a = (instruction >> 20) & 0x0f;
    b = (instruction >> 16) & 0x0f;
    c = (instruction >> 12) & 0x0f;
    d = instruction & 0x0fff;

    if(d & 0x800){ // negative offset for jumps
        d = -1 * ((~d & 0xfff) + 1);
    }

  if(a < 0 || a > 15 || b < 0 || b > 15 || c < 0 || c > 15){
    // Nevalidan registar
    std::cout << "Error: unvalid register: 0x" << std::hex <<  op_code << std::endl;
    //napraviPrekid(INSTRUKCIJSKA_GRESKA);
    return;
  }

    if(op_code == HALT){
        emulating = false;
    }
    else if(op_code == INT){
        napraviPrekid(SOFTVERSKI_PREKID);
    }
    else if(op_code == JMP_MEM){
        rpc = procitajInt(gp_registri[a] + d);
    }
    else if(op_code == JMP_IMM){
        rpc = gp_registri[a] + d;
    }
    else if(op_code == BGT_MEM){
        if(gp_registri[b] > gp_registri[c]){
        rpc = procitajInt(gp_registri[a] + d);
        }
    }
    else if(op_code == BGT_IMM){
        if(gp_registri[b] > gp_registri[c]){
        rpc = gp_registri[a] + d;
        }
    }
    else if(op_code == BNE_MEM){
        if(gp_registri[b] != gp_registri[c]){
        rpc = procitajInt(gp_registri[a] + d);
        }
    }
    else if(op_code == BNE_IMM){
        if(gp_registri[b] != gp_registri[c]){
        rpc = gp_registri[a] + d;
        }
    }
    else if(op_code == BEQ_MEM){
        if(gp_registri[b] == gp_registri[c]){
        rpc = procitajInt(gp_registri[a] + d);
        }
    }
    else if(op_code == BEQ_IMM){
        if(gp_registri[b] == gp_registri[c]){
        rpc = gp_registri[a] + d;
        }
    }
    else if(op_code == CALL_MEM){
        push(rpc);
        rpc = procitajInt(gp_registri[a] + d);
    }
    else if(op_code == CALL_IMM){
        push(rpc);
        rpc = gp_registri[a] + d;
    }
    else if(op_code == XCHG){
        unsigned long tmp = gp_registri[b];
        gp_registri[b] = gp_registri[c];
        gp_registri[c] = tmp;
    }
    else if(op_code == ADD){
        gp_registri[a] = gp_registri[b] + gp_registri[c];
    }
    else if(op_code == SUB){
        gp_registri[a] = gp_registri[b] - gp_registri[c];
    }
    else if(op_code == MUL){
        gp_registri[a] = gp_registri[b] * gp_registri[c];
    }
    else if(op_code == DIV){
        if(gp_registri[c] == 0){
        cout << "EMULATOR GRESKA: Deljenje nulom\n";
        napraviPrekid(INSTRUKCIJSKA_GRESKA);
        return;
        }
        gp_registri[a] = gp_registri[b] / gp_registri[c];
    }
    else if(op_code == NOT){
        gp_registri[a] = ~gp_registri[b];
    }
    else if(op_code == AND){
        gp_registri[a] = gp_registri[b] & gp_registri[c];
    }
    else if(op_code == OR){
        gp_registri[a] = gp_registri[b] | gp_registri[c];
    }
    else if(op_code == XOR){
        gp_registri[a] = gp_registri[b] ^ gp_registri[c];
    }
    else if(op_code == SHL){
        gp_registri[a] = gp_registri[b] << gp_registri[c];
    }
    else if(op_code == SHR){
        gp_registri[a] = gp_registri[b] >> gp_registri[c];
    }
    else if(op_code == CSRRD){
        gp_registri[a] = cs_registri[b];
    }
    else if(op_code == CSRWR){
        cs_registri[a] = gp_registri[b];
    }
    else if(op_code == PUSH){
        gp_registri[a] += d;
        upisiInt(gp_registri[a], gp_registri[c]);
    }
    else if(op_code == POP){
        gp_registri[a] = procitajInt(gp_registri[b]);
        gp_registri[b] += d;
    }
    else if(op_code == LD_MEM_REG){  
        gp_registri[a] = procitajInt(gp_registri[b] + d);
    }
    else if(op_code == LD_REG){
        gp_registri[a] = gp_registri[b] + d;
    }
    else if(op_code == ST_MEM){
        upisiInt(gp_registri[a] + gp_registri[b] + d, gp_registri[c]);
    }
    else if(op_code == ST_MEM_MEM){
        upisiInt(procitajInt(gp_registri[a] + gp_registri[b] + d), gp_registri[c]);
    }
    else if(op_code == CSRWR_MEM){
        cs_registri[a] = procitajInt(gp_registri[b] + gp_registri[c] + d);
    }
    else{
        cout << "EMULATOR GRESKA: Nepoznata instrukcija sa kodom operacije: 0x" << hex << op_code << endl;
    }
}



void Emulator::push(int podatak){
    sp -= 4;
    unsigned char* ptr = reinterpret_cast<unsigned char*>(&podatak);
    memory[sp] = ptr[3]; 
    memory[sp + 1] = ptr[2];
    memory[sp + 2] = ptr[1];
    memory[sp + 3] = ptr[0]; 
}

int Emulator::pop(){
    unsigned char byte_3 = memory[sp + 3];
    unsigned char byte_2 = memory[sp + 2];
    unsigned char byte_1 = memory[sp + 1];
    unsigned char byte_0 = memory[sp];     

    int podatak = (static_cast<int>(byte_3) << 24) |
                  (static_cast<int>(byte_2) << 16) |
                  (static_cast<int>(byte_1) << 8)  |
                  (static_cast<int>(byte_0));

    // Adjust stack pointer to point to the next position
    sp += 4; // Move stack pointer up by 4 bytes

    return podatak;
}


void Emulator::mk_interrupt(unsigned long cause){
  push(csrs[status]);
  push(pc);

  csrs[cause] = cause;
  pc = csrs[handler]; 

  csrs[status] |= 0x4; 
  csrs[status] |= 0x2; 
  csrs[status] |= 0x1; 
}
