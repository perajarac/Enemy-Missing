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
    #include <algorithm>
    #include <unordered_set>
    #include <map>
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
        struct literal_pool{
            unsigned _base;
            std::vector<int> literals;

            int return_index_of_literal(int literal){
                if(std::find(literals.begin(), literals.end(), literal>>8) != literals.end()){
                    auto it = std::find(literals.begin(), literals.end(), literal);
                    return std::distance(literals.begin(), it);
                }else{
                    literals.push_back(literal);
                    return literals.size()-1;
                }
            }
            
            void set_base(unsigned base){
                _base = base;
            }

            unsigned get_base(){
                return _base;
            }

        };

        static void make_section(std::string& section_name);

        static void handle_instruction(instruction op_code, std::vector<int> operands);

        static void handle_sys_regr(std::string& op_code, unsigned reg);

        static void handle_sys_regw(std::string& op_code, unsigned reg);

        static void add_symbol(const symbol& sym);

        static void write_memory_content();

        static void write_section_context();

        static void write_symbol_table_context();

        static void add_literal_pool_to_memory();

        static void end_last_section();

        static void resolve_literal_flink();
        static void resovle_symbol_flink();

        static void handle_skip(unsigned bytes);
        static void handle_word(const std::string& sym_name);
        static void handle_word(unsigned literal);
        static void handle_bind_type(bind_type bt, std::string sym_name);
        static void handle_ascii(std::string& ascii);

        //---------------------load------------------------------------
        static void mem_imm_literal(int literal, int reg);
        static void mem_dir_literal(int literal, int reg);
        static void mem_dir_offset_literal(int reg1, int literal, int reg2);
        static void mem_dir_register(int opr_reg, int reg);
        static void mem_ind_register(int opr_reg, int reg);
        static void mem_imm_symbol(std::string ident, int reg);
        static void mem_dir_symbol(std::string ident, int reg);
        //--------------------store------------------------------------
        static void st_mem_dir_literal(int reg, int address);
        static void st_mem_dir_offset_literal(int reg1, int literal, int reg2);
        static void st_mem_dir_reg(int reg1, int reg2);
        static void st_mem_dir_symbol(std::string ident, int reg);

        static void handle_label(std::string ident);

        static void mk_iret();
        static void mk_call(std::string ident);
        static void mk_call(int literal);
        static void pop(int reg, bool csr);
        static void push(int reg);
        static void jump_sym(instruction ins, int gpr1, int gpr2, std::string ident);
        static void jump_lit(instruction ins, int gpr1, int gpr2, int literal);

        static bool ass_end;

        static void set_output(std::string str);

    private:
        //helper functions
        static void arithmetic_operation(const std::string& arithmetic_code, const std::vector<int>& operands);

        static bool sym_exist(const std::string& sym_name);
        static int sym_index(const std::string& sym_name);

        static void wliteralim(int literal);
        static void wregim(int opr_reg, int reg);
        static void putlitip(int literal, int reg);
        static void wlitims(int literal, int reg);

        static std::string output_file;

        static std::ofstream ass_output;

        static unsigned current_address;

        static unsigned location_counter;

        static std::vector<section> section_tables;

        static std::vector<symbol> sym_table;

        static std::vector<std::pair<unsigned, std::string>> memory_content;

        static std::unordered_map<std::string, std::vector<int>> symbols_flink;

        static std::unordered_map<std::string, std::vector<int>> relocation_table;

        static literal_pool lit_pool;
        static std::map<unsigned, int> literal_flink; //map memory_address->index in literal pool

    };

    #endif