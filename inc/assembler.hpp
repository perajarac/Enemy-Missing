    #ifndef _assembler_hpp_
    #define _assembler_hpp_

    #include <string>
    #include <vector>
    #include <sstream>
    #include <iostream>
    #include <fstream>
    #include <iomanip>
    #include <memory>
    #include <unordered_map>



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
            GLOBAL, EXTERN, SECTION, WORD, SKIP, ASCII, END
        };

        enum address_type {
            INDIRECT_ADDRESSING, IND
        };

        enum bind_type {LOC, GLO, EXT};

        struct symbol{
            std::size_t _num;
            int _value;
            bind_type _bind;
            std::string _section_name;
            std::string _name;

            symbol(std::size_t num, int value, bind_type bind, std::string section_name, const std::string& name)
            : _num(num), _value(value), _bind(bind), _section_name(section_name), _name(name) {}  

            unsigned get_num() const;
            int get_value() const;
            bind_type get_bind() const;
            std::string get_section_name() const;
            std::string get_name() const;

            void set_num(unsigned num);
            void set_value(unsigned value);
            void set_bind(bind_type bind);
            void set_section_name(const std::string sec_name);
            void set_name(const std::string name);
            
        };
        struct section{
            std::string _name;
            unsigned _base;
            unsigned _length;

            section(const std::string& name, unsigned base)
            : _name(name), _base(base) {}

            unsigned get_length() const;
            unsigned get_base() const;
            std::string get_name() const;

            void set_length(unsigned length);
        };

        struct flink{
            unsigned address;
            flink(unsigned adr): address(adr) {}
        };
        
        static void make_section(std::string& section_name);

        static void handle_instruction(instruction op_code, std::vector<int> operands);

        static void handle_sys_regr(std::string& op_code, unsigned reg);

        static void handle_sys_regw(std::string& op_code, unsigned reg);

        static void add_symbol(const symbol& sym);

        static void write_memory_content();

        static void write_section_context();

        static void write_symbol_table_context();

        static void end_last_section();

        static void handle_skip(unsigned bytes);
        static void handle_word(const std::string& sym_name);
        static void handle_word(unsigned literal);
        static void handle_bind_type(bind_type bt, std::string sym_name);
        static void handle_ascii(std::string& ascii);


        //TODO: relocation tables

    private:
        //helper functions
        static void arithmetic_operation(const std::string& arithmetic_code, const std::vector<int>& operands);

        static bool sym_exist(const std::string& sym_name);

        static std::ofstream ass_output;

        static unsigned current_address;

        static unsigned location_counter;

        static std::vector<section> section_tables;

        static std::vector<symbol> sym_table;

        static std::vector<std::pair<unsigned, std::string>> memory_content;

        static std::unordered_map<std::string, std::vector<flink>> flink_table;

    };

    #endif