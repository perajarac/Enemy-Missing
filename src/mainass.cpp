#include <iostream>
#include <cstdio>
#include "../inc/assembler.hpp"
#include "../inc/parser.hpp"



extern FILE* yyin;


int main(int argc, char* argv[]) {
	char* input_file;
	char* output_file;

	if((std::string)argv[1] != "-o"){
		std::cout << "No output file given \n";
		return -1;
	}

	input_file = argv[3];
	output_file = argv[2];
	Assembler::set_output(output_file);
	
	FILE *file = fopen(input_file, "r");
	if(!file) printf("couldnt open file");

		yyin = file;

    do {
        yyparse();
    } while(!feof(yyin));

	Assembler::end_last_section();
	Assembler::local_sym_errors();
	if(Assembler::ass_end == false){
		Assembler::write_section_context();
		Assembler::write_symbol_table_context();
		Assembler::write_memory_content();
		Assembler::write_realoc();
		Assembler::write_object_file();
	}

	fclose(file);

	return 0;
}
