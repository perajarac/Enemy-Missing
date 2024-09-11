#include "../inc/linker.hpp"

std::vector<std::pair<std::string,std::string>> Linker::place_sections;
std::vector<std::string> Linker::input_files;
std::string Linker::output_file;
std::vector<file> Linker::files_content;

void Linker::set_input(std::vector<std::string> in){
    input_files = in;
}
void Linker::set_output(std::string out){
    output_file = out;
}

void Linker::set_place_sections(std::vector<std::pair<std::string,std::string>> ps){
    place_sections = ps;
}

void Linker::read_obj_files(){
    for(std::string input_file:input_files){
        
        std::ifstream obj_file(input_file, std::ios::binary);
        file current_file;
        
        //reading section table content of current file
        int section_table_size;
        obj_file.read(reinterpret_cast<char*>(&section_table_size), sizeof(int));
        for(int i = 0;i<section_table_size;i++){
            int sec_name_length;
            obj_file.read(reinterpret_cast<char*>(&sec_name_length), sizeof(int));
            std::string sec_name(sec_name_length,'\0');
            obj_file.read(&sec_name[0], sec_name_length);
            int section_base;
            obj_file.read(reinterpret_cast<char*>(&section_base), sizeof(int));
            int section_length;
            obj_file.read(reinterpret_cast<char*>(&section_length), sizeof(int));
            int section_lit_pool_base;
            obj_file.read(reinterpret_cast<char*>(&section_lit_pool_base), sizeof(int));

            section cur_sec(sec_name, section_base, section_length, section_lit_pool_base);
            current_file.add_section(cur_sec);
        }
        //reading symbol table content of current file
        int symbol_table_size;
        obj_file.read(reinterpret_cast<char*>(&symbol_table_size), sizeof(int));
        for(int i = 0;i<symbol_table_size;i++){
            int sym_name_length;
            obj_file.read(reinterpret_cast<char*>(&sym_name_length), sizeof(int));
            std::string sym_name(sym_name_length,'\0');
            obj_file.read(&sym_name[0], sym_name_length);

            int sym_value;
            obj_file.read(reinterpret_cast<char*>(&sym_value), sizeof(int));
            bind_type sym_bind;
            obj_file.read(reinterpret_cast<char*>(&sym_bind), sizeof(int));

            int section_name_length;
            obj_file.read(reinterpret_cast<char*>(&section_name_length), sizeof(int));
            std::string section_name(section_name_length, '\0');
            obj_file.read(&section_name[0], section_name_length);

            symbol cur_sym(sym_value, sym_bind, section_name, sym_name);
            current_file.add_symbol(cur_sym);
        }
        //reading reloc table content of current fille
        int reloc_table_size;
        obj_file.read(reinterpret_cast<char*>(&reloc_table_size), sizeof(int));
        for(int i = 0; i<reloc_table_size;i++){
            int sym_name_length;
            obj_file.read(reinterpret_cast<char*>(&sym_name_length), sizeof(int));
            std::string sym_name(sym_name_length,'\0');
            obj_file.read(&sym_name[0], sym_name_length);
            int reloc_vector_length;
            obj_file.read(reinterpret_cast<char*>(&reloc_vector_length), sizeof(int));
            std::vector<int> reloc_addresses;
            for(int j = 0; j < reloc_vector_length; j++){
                int curr;
                obj_file.read(reinterpret_cast<char*>(&curr), sizeof(int));
                reloc_addresses.push_back(curr);
            }
            current_file.add_reloc_table(sym_name,reloc_addresses);
        }
        //reading memory content
        int memory_content_size;
        std::vector<std::pair<int, std::string>> memory_content;
        obj_file.read(reinterpret_cast<char*>(&memory_content_size),sizeof(int));
        for(int i = 0; i < memory_content_size; i++){
            std::string byte(2, '\0');
            obj_file.read(&byte[0],2);
            memory_content.push_back({i,byte});
        }
        current_file.memory_content = memory_content;
        //adds file content
        files_content.push_back(current_file);
    }
}