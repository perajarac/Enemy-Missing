#include "../inc/emulator.hpp"


std::vector<int> Emulator::gprs(15,0);
std::vector<int> Emulator::csrs(3,0);
int& Emulator::sp = gprs[14];
int& Emulator::pc = gprs[15];
std::vector<section> Emulator::sections;
bool Emulator::emulating = false;
bool Emulator::term_int = false;

std::map<int,char> Emulator::memory;
std::string Emulator::obj_hex;

int Emulator::counter = 0;

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
        return static_cast<unsigned char>(byte & 0xff);
    };
    for (const section& sec : sections) {
        int base = sec.get_base();  
        for (const auto& mem_pair : sec.memory_content) {
            int offset = mem_pair.first;
            unsigned char byte_value = hex_string_to_byte(mem_pair.second);
            int dest_address = base + offset;
            memory[dest_address] = (byte_value & 0xff);
        }

    }

}

void Emulator::lae_ins(){
    op_codes op_code;
    int a,b,c,d;
    auto it = memory.find(pc);
    if (it == memory.end()) {
        std::cout << "PC fault, nothing on that address:" << std::hex << pc << std::endl;
        return;
    }
    uint instruction = read(pc);
    
    op_code = (op_codes)(instruction >> 24);
    a = (instruction >> 20) & 0x0f;
    b = (instruction >> 16) & 0x0f;
    c = (instruction >> 12) & 0x0f;
    d = instruction & 0x0fff;

    //std::cout << std::hex << pc << ":";
    // std::cout << " ins: " << std::hex <<  op_code << a << b << c << d  << std::flush;
    // std::cout << "r1: " << std::hex <<gprs[1] << " r2: " << std::hex << gprs[2] << std::endl << std::flush;
    pc += 4;

    if(d & 0x800){ // negative offset for jumps
        d = -1 * ((~d & 0xfff) + 1);
    }

    if(a < 0 || a > 15 || b < 0 || b > 15 || c < 0 || c > 15){
        // Nevalidan registar
        std::cout << "Error: unvalid register: 0x" << std::hex <<  op_code << std::endl;
        mk_interrupt(ins_fault);
        return;
    }

    if(op_code == HALT){
        emulating = false;
    }
    else if(op_code == INT){
        mk_interrupt(soft_int);
    }
    else if(op_code == JMP_MEM){
        pc = read(gprs[a] + d - 4);
    }
    else if(op_code == JMP_IMM){
        pc = gprs[a] + d - 4;
    }
    else if(op_code == BGT_MEM){
        if(gprs[b] > gprs[c]){
        pc = read(gprs[a] + d - 4);
        }
    }
    else if(op_code == BGT_IMM){
        if(gprs[b] > gprs[c]){
            pc = gprs[a] + d - 4;
        }
    }
    else if(op_code == BNE_MEM){
        if(gprs[b] != gprs[c]){
        pc = read(gprs[a] + d - 4);
        }
    }
    else if(op_code == BNE_IMM){
        if(gprs[b] != gprs[c]){
            pc = gprs[a] + d - 4;
        }
    }
    else if(op_code == BEQ_MEM){
        if(gprs[b] == gprs[c]){
            pc = read(gprs[a] + d - 4);
        }
    }
    else if(op_code == BEQ_IMM){
        if(gprs[b] == gprs[c]){
            pc = gprs[a] + d - 4;
        }
    }
    else if(op_code == CALL_MEM){
        push(pc);
        pc = read(gprs[b] + d - 4);

    }
    else if(op_code == CALL_IMM){
        push(pc);
        pc = gprs[b] + d - 4;
    }
    else if(op_code == XCHG){
        unsigned long tmp = gprs[b];
        gprs[b] = gprs[c];
        gprs[c] = tmp;
    }
    else if(op_code == ADD){
        gprs[a] = gprs[b] + gprs[c];
    }
    else if(op_code == SUB){
        gprs[a] = gprs[b] - gprs[c];
    }
    else if(op_code == MUL){
        gprs[a] = gprs[b] * gprs[c];
    }
    else if(op_code == DIV){
        if(gprs[c] == 0){
        std::cout << "Error: null division\n";
        mk_interrupt(ins_fault);
        return;
        }
        gprs[a] = gprs[b] / gprs[c];
    }
    else if(op_code == NOT){
        gprs[a] = ~gprs[b];
    }
    else if(op_code == AND){
        gprs[a] = gprs[b] & gprs[c];
    }
    else if(op_code == OR){
        gprs[a] = gprs[b] | gprs[c];
    }
    else if(op_code == XOR){
        gprs[a] = gprs[b] ^ gprs[c];
    }
    else if(op_code == SHL){
        gprs[a] = gprs[b] << gprs[c];
    }
    else if(op_code == SHR){
        gprs[a] = gprs[b] >> gprs[c];
    }
    else if(op_code == CSRRD){
        gprs[a] = csrs[b];
    }
    else if(op_code == CSRWR){
        csrs[a] = gprs[b];
    }
    else if(op_code == PUSH){
        push(gprs[c]);
    }
    else if(op_code == POP){
        gprs[a] = pop();
    }
    else if(op_code == LD_MEM_REG){  
        if(b == 15){
            gprs[a] = read(gprs[b] + d - 4);
        }else{
            gprs[a] = read(gprs[b] + d);
            // std::cout << std::hex  << "majmun: " << read(0xffffff04) << std::endl << std::flush;

        }
    }
    else if(op_code == LD_REG){
        gprs[a] = gprs[b] + d;
    }
    else if(op_code == ST_MEM){
        write(gprs[a] + gprs[b] + d, gprs[c]);
    }
    else if(op_code == ST_MEM_MEM){
        if(b == 15){
            write(read(gprs[a] + gprs[b] + d - 4), gprs[c]);
        }else{
            write(read(gprs[a] + gprs[b] + d), gprs[c]);

        }
    }
    else if(op_code == CSRWR_MEM){
        csrs[a] = read(gprs[b] + gprs[c] + d);
    }else if(op_code == CSRWR_MEM_POSTINC){
        csrs[a] = pop();
    }
    else{
        std:: cout << "Error, unknown instruction on address x" << std::hex << op_code << std::endl;
    }


}


//write and read 4bytes
void Emulator::write(int address, int data){
    if(address == term_out){
        std::cout << (char)data << std::flush;
    }
    unsigned char* ptr = reinterpret_cast<unsigned char*>(&data);
    memory[address] = ptr[3]; 
    memory[address + 1] = ptr[2];
    memory[address + 2] = ptr[1];
    memory[address + 3] = ptr[0]; 
}

int Emulator::read(int address){
    unsigned int byte_3 = static_cast<unsigned char>(memory[address])&0xff;
    unsigned int byte_2 = static_cast<unsigned char>(memory[address + 1])&0xff;
    unsigned int byte_1 = static_cast<unsigned char>(memory[address + 2])&0xff;
    unsigned int byte_0 = static_cast<unsigned char>(memory[address + 3])&0xff;


    
    int data = (static_cast<int>(byte_3) << 24) |
                  (static_cast<int>(byte_2) << 16) |
                  (static_cast<int>(byte_1) << 8)  |
                  (static_cast<int>(byte_0));


    return data;
}



void Emulator::push(int data){
    sp -= 4;
    unsigned char* ptr = reinterpret_cast<unsigned char*>(&data);
    memory[sp] = ptr[3]; 
    memory[sp + 1] = ptr[2];
    memory[sp + 2] = ptr[1];
    memory[sp + 3] = ptr[0]; 
}

int Emulator::pop(){
    unsigned char byte_3 = memory[sp];
    unsigned char byte_2 = memory[sp + 1];
    unsigned char byte_1 = memory[sp + 2];
    unsigned char byte_0 = memory[sp + 3];     

    int data = (static_cast<int>(byte_3) << 24) |
                  (static_cast<int>(byte_2) << 16) |
                  (static_cast<int>(byte_1) << 8)  |
                  (static_cast<int>(byte_0));

    // Adjust stack pointer to point to the next position
    sp += 4; // Move stack pointer up by 4 bytes
    return data;
}


void Emulator::mk_interrupt(int uzrok){
    push(pc);
    push(csrs[status]);

    csrs[cause] = uzrok;
    pc = csrs[handler]; 

    csrs[status] |= 0x4; 
    csrs[status] |= 0x2; 
    csrs[status] |= 0x1; 
}


void Emulator::setup(){
    pc = start_memory;
    sp = mmap_registers_addr;

    csrs[status] &= ~0x4; //set soft intr
    csrs[status] &= ~0x2; //set terminal intr
    csrs[status] &= ~0x1; //set timer intr ? no need?
    emulating = true;
}


void Emulator::write_reg(){
  std::cout << std::endl;
  std::cout << "----------------------------------------------------------------------" << std::endl;
  std::cout << "Emulated processor executed halt instruction.\n";
  std::cout << "Emulated processor state:\n";
  for(int i = 0; i < 16; i++){
    std::string reg = "r" + std::to_string(i);
    std::cout << "\t" << std::setw(3) << std::setfill(' ') << reg << "=0x" << std::setw(8) << std::hex << std::setfill('0') << gprs[i];
    if(i % 4 == 3) std::cout <<  std::endl;
  }
  std::cout << std::endl;
}

struct termios old_setup;
struct termios new_setup;


void Emulator::setup_terminal(){
  tcgetattr(STDIN_FILENO, &old_setup);
  
  new_setup = old_setup;

  new_setup.c_lflag &= ~(ECHO |ECHONL | ICANON | IEXTEN);
  
  new_setup.c_cc[VTIME] = 0; 
  new_setup.c_cc[VMIN] = 0; 

  tcsetattr(STDIN_FILENO, TCSAFLUSH, &new_setup);

}

void Emulator::restart_terminal(){
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &old_setup);
}

void Emulator::read_from_stdin(){
  char character;
  if(::read(STDIN_FILENO, &character, 1) == 1){
    write(term_in, character); 
    term_int = true;
  }
}
