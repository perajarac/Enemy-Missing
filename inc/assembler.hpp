    #ifndef _assembler_hpp_
    #define _assembler_hpp_

    #include <string>
    #include <vector>
    #include <sstream>
    #include <iostream>
    #include <fstream>
    #include <iomanip>



    //tabelea simbola, tabela sekcija, relokaciona tabela

    class Assembler{
    public:

        enum instruction {
            HALT_CODE, INT_CODE, IRET_CODE, CALL_CODE, RET_CODE,JMP_CODE, BEQ_CODE, BNE_CODE, BGT_CODE,
            PUSH_CODE, POP_CODE, XCHG_CODE, ADD_CODE, SUB_CODE, MUL_CODE, DIV_CODE,
            NOT_CODE, AND_CODE, OR_CODE, XOR_CODE, SHL_CODE, SHR_CODE,
            LD_CODE, ST_CODE, CSRRD_CODE, CSRWR_CODE
        };

        enum directive {
            GLOBAL, EXTERN, SECTION, WORD, SKIP, ASCII, ECU
        };

        enum address_type {
            INDIRECT_ADDRESSING, IND
        };

        enum bind_type {LOC, GLO};

        struct symbol{
            unsigned _num;
            unsigned _value;
            unsigned _size;
            bind_type _bind;
            unsigned _section_index;
            std::string _name;

            symbol(unsigned num, unsigned value, unsigned size, bind_type bind, unsigned section_index, const std::string& name)
            : _num(num), _value(value), _size(size), _bind(bind), _section_index(section_index), _name(name) {}  
            
        };
        struct section{
            std::string _name;
            unsigned _base;
            unsigned _length;

            section(const std::string& name, unsigned base)
            : _name(name), _base(base) {}

            unsigned get_length() const {
                return _length;
            }

            unsigned get_base() const {
                return _base;
            }

            std::string get_name() const {
                return _name;
            }

            void set_length(unsigned length){
                _length = length;
            }
        };

        static void make_section(std::string& section_name);

        static void handle_instruction(instruction op_code, std::vector<int> operands);

        static void handle_directive(directive directive, unsigned location_counter);

        static void handle_sys_regr(std::string& op_code, unsigned reg);

        static void handle_sys_regw(std::string& op_code, unsigned reg);

        static void add_symbol(const symbol& sym);

        static void write_memory_content();

        static void write_section_context();

        static void end_last_section();

        //TODO: relocation tables

    private:
        //helper functions
        static void arithmetic_operation(const std::string& arithmetic_code, const std::vector<int>& operands);

        static std::ofstream ass_output;

        static unsigned current_address;

        static unsigned location_counter;

        static std::vector<section> section_tables;

        static std::vector<symbol> symbol_tables;

        static std::vector<std::pair<unsigned, std::string>> memory_content;

    };


    #endif