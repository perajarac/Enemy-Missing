    #ifndef _linker_hpp_
    #define _linker_hpp_

#include "../inc/common.hpp"




class Linker{
public:
    static void set_input(std::vector<std::string> in);
    static void set_output(std::string out);
    static void set_place_sections(std::vector<std::pair<std::string,std::string>> place_sections);







private:
    static std::map<int, std::string> memory_content;


    static std::vector<std::pair<std::string,std::string>> place_sections;
    static std::vector<std::string> input_files;
    static std::string output_file;
};







#endif