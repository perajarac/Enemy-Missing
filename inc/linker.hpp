    #ifndef _linker_hpp_
    #define _linker_hpp_

#include "../inc/common.hpp"




class Linker{
public:
    static void set_input(std::vector<std::string> in);
    static void set_output(std::string out);
    static void set_place_sections(std::vector<std::pair<std::string,int>> place_sections);

    static void read_obj_files();
    static void merge_same_sections();
    static void map_sections();
    static void merge_symbol_tables();
    static void merge_relocation_tables();
    static void merge_memory_contents();
    static void resolve_relocations();
    static void make_object_file();


    static void print_sections_and_mem_content();

    static bool is_hex;
private:

    static void copy_section_memory_content(const std::vector<std::pair<int, std::string>>& file_memmory_content,section& sec);
    static void copy_section_memory_content(const std::map<int, std::string>& file_memmory_content,section& sec);
    static void check_overlapping();

    static void concat_memmory_content(const section& sec_to_concat);

    static symbol get_sym(std::string& sym_name);
    


    static std::vector<file> files_content;
    
    static std::map<int, std::string> memory_content;

    static std::unordered_map<std::string,std::vector<section>> merged_sec_table;
    static std::vector<std::string> section_order;

    static std::vector<symbol> merged_sym_table;
    static std::vector<reloc_node> merged_relocation_table;



    static std::vector<std::pair<std::string,int>> place_sections;

    static std::vector<std::string> input_files;
    static std::string output_file;


};







#endif