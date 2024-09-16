#include "../inc/linker.hpp"

std::vector<std::pair<std::string,int>> Linker::place_sections;
std::vector<std::string> Linker::input_files;
std::string Linker::output_file;
std::vector<file> Linker::files_content;
bool Linker::is_hex = false;

std::unordered_map<std::string,std::vector<section>> Linker::merged_sec_table;
std::vector<std::string> Linker::section_order;

std::vector<symbol> Linker::merged_sym_table;

void Linker::set_input(std::vector<std::string> in){
    input_files = in;
}
void Linker::set_output(std::string out){
    output_file = out;
}

void Linker::set_place_sections(std::vector<std::pair<std::string,int>> ps){
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

            //reading reloc table content of current section
            int reloc_table_size;
            obj_file.read(reinterpret_cast<char*>(&reloc_table_size), sizeof(int));
            for(int i = 0; i<reloc_table_size;i++){
                int sym_name_length;
                obj_file.read(reinterpret_cast<char*>(&sym_name_length), sizeof(int));
                std::string sym_name(sym_name_length,'\0');
                obj_file.read(&sym_name[0], sym_name_length);
                int reloc_offset;
                obj_file.read(reinterpret_cast<char*>(&reloc_offset), sizeof(int));
                int reloc_addend;
                obj_file.read(reinterpret_cast<char*>(&reloc_addend), sizeof(int));
                bool reloc_is_section;
                obj_file.read(reinterpret_cast<char*>(&reloc_is_section), sizeof(bool));
                cur_sec.relocation_table.push_back({reloc_offset,sym_name,reloc_addend,reloc_is_section});
            }

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

        //map sections and its memmory
        for(auto& sec:current_file.section_tables){
            copy_section_memory_content(current_file.memory_content, sec);
        }
        //adds file content
        files_content.push_back(current_file);

    }
}

void Linker::merge_same_sections(){
    for(auto place_sec:place_sections){
        merged_sec_table[place_sec.first]; //place on first place section that was declared with -place
        section_order.push_back(place_sec.first);
    }

    for (auto& file : files_content) {
        for(section& section : file.section_tables) {
            auto it = merged_sec_table.begin();
            for(; it != merged_sec_table.end(); it++){
                if(it->first == section.get_name()) break; //check if current section is already in merged sections
            }
            if(it == merged_sec_table.end()){ //if not add new section
                section._base = 0;
                merged_sec_table[section.get_name()].push_back(section);
                section_order.push_back(section.get_name());
            }else{ //if is, update relocation table entries, update start of literal pool base and concat current section on vector of merged sections
                int length = count_sec_length(it->second); //calculate addend to rel tb entr and lit pool base and base adr
                section._lit_pool_base += length;
                section._base = length;
                for(auto& rel_entry:section.relocation_table){
                    rel_entry.offset += length;
                    if(rel_entry.is_section) rel_entry.addend += length;
                }
                merged_sec_table[section.get_name()].push_back(section);
            }
            for(auto& sym : file.sym_table){
                if(sym.get_section_name() == section.get_name()) {
                    sym.set_value(sym.get_value() + section.get_base());
                }
            }
        }
    }
}

void Linker::copy_section_memory_content(const std::vector<std::pair<int, std::string>>& file_memmory_content,section& sec){
    std::vector<std::pair<int, std::string>> local_memory_content;

    unsigned section_base = sec.get_base();
    unsigned section_end = section_base + sec.get_length();
    for (const auto& mem : file_memmory_content) {
        int address = mem.first;
        // Check if the address is within the section's range
        if (address >= section_base && address < section_end) {
            local_memory_content.push_back(mem);
        }
    }
    sec.memory_content = local_memory_content;
}

void Linker::merge_symbol_tables(){
    std::vector<symbol> extern_symbols;

    for(auto file:files_content){
        for(auto sym:file.sym_table){
            if(sym.get_bind() == bind_type::EXT){
                extern_symbols.push_back(sym);
            }else{
                if(sym.get_bind() == bind_type::GLO){
                    if(std::find(merged_sym_table.begin(), merged_sym_table.end(), sym)!=merged_sym_table.end()){
                        std::cout << "Error, multiple definition of symbol: " << sym.get_name();
                        exit(1);
                    }

                    auto sec_it = merged_sec_table.find(sym.get_section_name());
                    if (sec_it != merged_sec_table.end() && !sec_it->second.empty()) {
                        sym.set_value(sec_it->second[0].get_base() + sym.get_value()); //postavi vrednost simbola ako je sekcija definisana
                        merged_sym_table.push_back(sym);
                    }
                }
            }
        }
    }

    for(auto& ex_sym:extern_symbols){
        auto it = std::find(merged_sym_table.begin(), merged_sym_table.end(), ex_sym);
        if(it != merged_sym_table.end()) continue;
        // simbol je eksteran a nema ga u tabeli 
        if(is_hex){ // Ako treba da generisemo izvrsni fajl ovo je greska
            std::cout << "Error, extern symbol " << ex_sym.get_name() << " is not defined in any file " << std::endl;
            exit(-1);
        }
        else{ // A ako je u pitanju relokativni fajl onda jednostavno dodamo simbol kao eksterni
            merged_sym_table.push_back(ex_sym);
        }
        
  }

}

void Linker::check_overlapping(){
    for(auto i = place_sections.begin(); i != place_sections.end(); i++){
        for(auto j = place_sections.begin(); j != place_sections.end(); j++){
            if(i->first == j->first) continue; // skip if sections are same
            // adr1-----------adr1+vel1     adr2----------------adr2+vel2 ako max(adr1,adr2) < min(adr1+vel1, adr2+vel2) onda ima presek
            if(std::max(merged_sec_table[i->first][0].get_base(), merged_sec_table[j->first][0].get_base()) < 
                std::min(merged_sec_table[i->first][0].get_base() + count_sec_length(merged_sec_table[i->first]), 
                    merged_sec_table[j->first][0].get_base() + count_sec_length(merged_sec_table[j->first]))){
                std::cout << "Error: sections overlapping due to -place: " << i->first << " and " << j->first << std::endl;
                exit(-1);
            }
        }
  }
}

void Linker::map_sections(){

    // Map sections that has been declared as argument -place
    int first_free_address = 0;
    for(auto &elem : place_sections){
        auto i = merged_sec_table.find(elem.first);
        if(i == merged_sec_table.end()){
            std::cout << "Error: -place used with unknown section: " << elem.first << std::endl;
            exit(-1);
        }
        auto& vector_of_merged_sections = merged_sec_table[elem.first];
        vector_of_merged_sections[0]._base = elem.second;
        int skip_first = 1;
        for(auto& section : vector_of_merged_sections){
            if(skip_first == 1) {
                skip_first--;
                continue; // skip base section of merged sections
            }
            section._base += elem.second;
            section._lit_pool_base += elem.second;
        }

        if(vector_of_merged_sections[0].get_base() + count_sec_length(vector_of_merged_sections) > first_free_address){ //next section should always start from max adr + sec.len in -place arg
            first_free_address = vector_of_merged_sections[0].get_base() + count_sec_length(vector_of_merged_sections);
        }
    }

    // Check for overlapping
    check_overlapping(); // Error if overlapps

    // Map rest of the sections
    for(std::string sec_name : section_order){
        auto it = std::find_if(place_sections.begin(), place_sections.end(), //find if section name is in place vector, we have handled that situation upper, so we skip it
                       [&sec_name](const std::pair<std::string, int>& elem) {
                           return elem.first == sec_name;
                       });
        if(it != place_sections.end()) continue;
        auto& vector_of_merged_sections = merged_sec_table[sec_name];
        vector_of_merged_sections[0]._base = first_free_address;
        int skip_first = 1;
        for(auto& section : vector_of_merged_sections){
            if(skip_first == 1) {
                skip_first--;
                continue; // skip base section of merged sections
            }
            section._base += first_free_address;
            section._lit_pool_base +=first_free_address;
        }
        first_free_address = vector_of_merged_sections[0]._base + count_sec_length(vector_of_merged_sections);
    }
}


void Linker::print_sections_and_mem_content(){
    std::ofstream ass_output;
    ass_output.open("linkertest.txt", std::ios::app);
    ass_output << "----------Table of sections----------\n";

    ass_output << std::left << std::setw(15) << "Name:" 
               << std::setw(15) << "Start:" 
               << std::setw(15) << "Size:" 
               << "\n";
    
    for(auto section:merged_sec_table){
        
        int length = count_sec_length(section.second);

        ass_output << std::left << std::setw(15) << section.first 
                   << std::setw(15);
        ass_output << std::hex << section.second[0].get_base();
        ass_output << std::setw(15) << std::hex << length << "\n";
        // ass_output << "------------Merged memory-----------\n";
        // int current_address = 0;
        // for(auto member:section.second){
        //     for(int i = 0;i < member.memory_content.size();i++){
        //         if(current_address % 8 == 0){
        //         if(current_address!=0)ass_output << "\n";
        //         std::stringstream ss;
        //         ss << std::hex << current_address << ":";
        //         ass_output << ss.str();
        //         }
        //         ass_output << "\t" << member.memory_content[i].second;
        //         current_address ++;
        //     }
        // }
    }

    ass_output << "----------------Reloc Table----------------\n";

    ass_output << std::left << std::setw(20) << "Section:" << std::setw(20) << "Symbol:" 
            << std::setw(10) << "Offset:" << std::setw(10) << "Addend:" <<  "\n";

    for (const auto& member : merged_sec_table) {
        ass_output << std::left << std::setw(20) << member.first << "\n"; // New line for each section
        for(auto section:member.second)
        for (const auto& reloc_node : section.relocation_table) {
            ass_output << std::setw(20) << ""  // Empty column for section name to align
                    << std::setw(20) << reloc_node.symbol_name
                    << std::setw(20) << reloc_node.offset
                    << std::setw(20) << reloc_node.addend;

            
            ass_output << "\n";  // New line for each symbol
        }
    }

    ass_output << "---------------------------------------------\n";


    ass_output << "----------------Symbol Table----------------\n";
    
    ass_output << std::left << std::setw(10) << "Num:" 
               << std::setw(10) << "Value:" 
               << std::setw(15) << "Bind:" 
               << std::setw(15) << "Section:" 
               << std::setw(15) << "Name:" << "\n";
    for (const auto& sym : merged_sym_table) {
        ass_output << std::left << std::setw(10) << sym.get_num();

        ass_output << std::setw(10) << std::hex << sym.get_value();

        ass_output << std::setw(15) << sym.get_bind()
                   << std::setw(15) << sym.get_section_name()
                   << std::setw(15) << sym.get_name() << "\n";
    }

    ass_output << "---------------------------------------------\n";
}