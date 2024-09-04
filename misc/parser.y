	%{
	#include <string.h>
	#include <stdio.h>
	#include "../inc/assembler.hpp"

	extern int yylex();
	extern int yyparse();
	extern FILE* yyin;

	extern int line_number;

	bool ass_end = false;

	void yyerror(const char* s);

	class Assembler;

	%}


	%defines "inc/parser.hpp"
	

	%union {
		int num;
		int op_code;
		char* ident;
	}

	%token<op_code> TOKEN_HALT
	%token<op_code> TOKEN_INT
	%token<op_code> TOKEN_IRET
	%token<op_code> TOKEN_CALL
	%token<op_code> TOKEN_RET
	%token<op_code> TOKEN_JMP
	%token<op_code> TOKEN_BEQ
	%token<op_code> TOKEN_BNE
	%token<op_code> TOKEN_BGT
	%token<op_code> TOKEN_PUSH
	%token<op_code> TOKEN_POP
	%token<op_code> TOKEN_XCHG
	%token<op_code> TOKEN_ADD
	%token<op_code> TOKEN_SUB
	%token<op_code> TOKEN_MUL
	%token<op_code> TOKEN_DIV
	%token<op_code> TOKEN_NOT
	%token<op_code> TOKEN_AND
	%token<op_code> TOKEN_OR
	%token<op_code> TOKEN_XOR
	%token<op_code> TOKEN_SHL
	%token<op_code> TOKEN_SHR
	%token<op_code> TOKEN_LD
	%token<op_code> TOKEN_ST
	%token<op_code> TOKEN_CSRRD
	%token<op_code> TOKEN_CSRWR


	%token<num> TOKEN_GLOBAL
	%token<num> TOKEN_EXTERN
	%token<num> TOKEN_SECTION
	%token<num> TOKEN_WORD
	%token<num> TOKEN_SKIP
	%token<num> TOKEN_ASCII
	%token TOKEN_END

	%token<ident> TOKEN_IDENT

	%token TOKEN_LPAR   // Left Parenthesis (
	%token TOKEN_RPAR   // Right Parenthesis )
	%token TOKEN_LBRACKET   // Left Bracket [
	%token TOKEN_RBRACKET   // Right Bracket ]
	%token TOKEN_PLUS   // Plus +
	%token TOKEN_MINUS  // Minus -
	%token TOKEN_PERCENT   // Percent %
	%token TOKEN_DOLLAR   // Dollar $
	%token TOKEN_SEMI   // Semicolon ;
	%token TOKEN_COLON   // Colon :
	%token TOKEN_COMMA   // Comma ,

	%token<num> TOKEN_REG   // General Purpose Registers (r0-r13)


	%token<ident> TOKEN_STATUS   // Status Register
	%token<ident> TOKEN_HANDLER   // Handler Register
	%token<ident> TOKEN_CAUSE   // Cause Register

	%token<num> TOKEN_NUM
	%token<ident> TOKEN_STRING



	%type<ident> sys_reg;





	%%
	prog
		: statements
		;


	statements
		:
		| statements statement
		;

	statement
		: directive
		| instr
		;

	directive
		: TOKEN_GLOBAL global_list
		| TOKEN_EXTERN extern_list
		| TOKEN_SECTION TOKEN_IDENT  
		{
			std::string ident = $2;
			Assembler::make_section(ident);
		}
		| TOKEN_WORD word_list
		| TOKEN_SKIP TOKEN_NUM {
			Assembler::handle_skip($2);
		}
		| TOKEN_ASCII TOKEN_STRING {
			std::string ascii = $2;
			ascii = ascii.substr(1,ascii.size()-2);
			Assembler::handle_ascii(ascii);
		}
		| TOKEN_END {
			ass_end = true;
		}
		| TOKEN_IDENT TOKEN_COLON  {
			
		}
		;

	global_list
		: TOKEN_IDENT {
			std::string ident = $1;
			Assembler::handle_bind_type(Assembler::bind_type::GLO, ident);
		}
		| global_list TOKEN_COMMA TOKEN_IDENT {
			std::string ident = $3;
			Assembler::handle_bind_type(Assembler::bind_type::GLO, ident);
		}
		;

	extern_list
		: TOKEN_IDENT {
			std::string ident = $1;	
			Assembler::handle_bind_type(Assembler::bind_type::EXT, ident);
			
		}
		| extern_list TOKEN_COMMA TOKEN_IDENT {
			std::string ident = $3;
			Assembler::handle_bind_type(Assembler::bind_type::EXT, ident);
		}
		;

	word_list
		: word
		| word_list TOKEN_COMMA word
		;

	word
		: TOKEN_IDENT {
			std::string temp = $1;
			Assembler::handle_word(temp);
		}
		| TOKEN_NUM {
			Assembler::handle_word($1);
		}
		;


	instr
		: TOKEN_HALT
			{
				Assembler::handle_instruction((Assembler::instruction)$1, {});
			}
		| TOKEN_INT{
				Assembler::handle_instruction((Assembler::instruction)$1, {});
			}
		| TOKEN_ADD TOKEN_REG TOKEN_COMMA TOKEN_REG
			{ 
				Assembler::handle_instruction((Assembler::instruction)$1, {$2, $4});
			}

		| TOKEN_SUB TOKEN_REG TOKEN_COMMA TOKEN_REG
			{ 
				Assembler::handle_instruction((Assembler::instruction)$1, {$2, $4});
			}

		| TOKEN_MUL TOKEN_REG TOKEN_COMMA TOKEN_REG
			{ 
				Assembler::handle_instruction((Assembler::instruction)$1, {$2, $4});
			}

		| TOKEN_DIV TOKEN_REG TOKEN_COMMA TOKEN_REG
			{ 
				Assembler::handle_instruction((Assembler::instruction)$1, {$2, $4});
			}
		| TOKEN_NOT TOKEN_REG
			{ 
				Assembler::handle_instruction((Assembler::instruction)$1, {0, $2});
			}
		| TOKEN_AND TOKEN_REG TOKEN_COMMA TOKEN_REG
			{ 
				Assembler::handle_instruction((Assembler::instruction)$1, {$2, $4});
			}

		| TOKEN_OR TOKEN_REG TOKEN_COMMA TOKEN_REG
			{ 
				Assembler::handle_instruction((Assembler::instruction)$1, {$2, $4});
			}

		| TOKEN_XOR TOKEN_REG TOKEN_COMMA TOKEN_REG
			{ 
				Assembler::handle_instruction((Assembler::instruction)$1, {$2, $4});
			}
		| TOKEN_SHL TOKEN_REG TOKEN_COMMA TOKEN_REG
			{ 
				Assembler::handle_instruction((Assembler::instruction)$1, {$2, $4});
			}

		| TOKEN_SHR TOKEN_REG TOKEN_COMMA TOKEN_REG
			{ 
				Assembler::handle_instruction((Assembler::instruction)$1, {$2, $4});
			}
		| TOKEN_XCHG TOKEN_REG TOKEN_COMMA TOKEN_REG
			{ 
				Assembler::handle_instruction((Assembler::instruction)$1, {$2, $4});
			}
		| TOKEN_CSRRD sys_reg TOKEN_COMMA TOKEN_REG
			{ 
				std::string ident = $2;
				Assembler::handle_sys_regr(ident, $4); 
			}
		| TOKEN_CSRWR TOKEN_REG TOKEN_COMMA sys_reg
			{ 
				std::string ident = $4;
				Assembler::handle_sys_regw(ident, $2); 
			}

		| TOKEN_LD TOKEN_DOLLAR TOKEN_NUM TOKEN_COMMA TOKEN_REG
			{ 
				Assembler::mem_imm_literal($3, $5);
			}
		| TOKEN_LD TOKEN_NUM TOKEN_COMMA TOKEN_REG
			{
				Assembler::mem_dir_literal($2, $4);
			}
		| TOKEN_LD TOKEN_LBRACKET TOKEN_REG TOKEN_PLUS TOKEN_NUM TOKEN_RBRACKET TOKEN_COMMA TOKEN_REG
			{
				Assembler::mem_dir_offset_literal($3,$5,$8);
			}
		| TOKEN_LD TOKEN_REG TOKEN_COMMA TOKEN_REG
			{
				Assembler::mem_dir_register($2, $4);
			}
		| TOKEN_LD TOKEN_LBRACKET TOKEN_REG TOKEN_RBRACKET TOKEN_COMMA TOKEN_REG
			{
				Assembler::mem_ind_register($3,$6);
			}

			/* TODO: ADD LOAD WITH SIMBOLS */
		| TOKEN_ST TOKEN_REG TOKEN_COMMA TOKEN_DOLLAR TOKEN_NUM
			{
				std::cout << "Unvalid instruction: store can not be executed with immediate operand\n";
			}
		| TOKEN_ST TOKEN_REG TOKEN_COMMA TOKEN_DOLLAR TOKEN_IDENT
			{
				std::cout << "Unvalid instruction: store can not be executed with immediate operand\n";
			}
		| TOKEN_ST TOKEN_REG TOKEN_COMMA TOKEN_NUM
			{	
				Assembler::st_mem_dir_literal($2,$4);
			}
		| TOKEN_ST TOKEN_LBRACKET TOKEN_REG TOKEN_RBRACKET TOKEN_COMMA TOKEN_REG
			{	
				Assembler::st_mem_dir_reg($3,$6);
			}
		




		/* | TOKEN_LD op TOKEN_COMMA TOKEN_REG
			{ if (!ended) mk_ld($2, $4); free_op($2); }
		| TOKEN_ST TOKEN_REG TOKEN_COMMA op
			{ if (!ended) mk_st($2, $4); free_op($4); } */
		/* | TOKEN_CSRRD csreg TOKEN_COMMA TOKEN_REG
			{ if (!ended) mk_csrrd($2, $4); }
		| TOKEN_CSRWR TOKEN_REG TOKEN_COMMA csreg
			{ if (!ended) mk_csrwr($2, $4); } */
		/*| TOKEN_IRET
			{ if (!ended) mk_iret(); }
		| TOKEN_CALL spec_operand
			{ if (!ended) mk_call($2); free_op($2);}
		| TOKEN_RET
			{ if (!ended) mk_pop(PC_CODE); }
		| TOKEN_JMP spec_operand
			{ if (!ended) mk_jmp($2); free_op($2); }
		| TOKEN_BEQ TOKEN_REG TOKEN_COMMA TOKEN_REG TOKEN_COMMA spec_operand
			{ if (!ended) mk_branch(0x31, $2, $4, $6); free_op($6); }
		| TOKEN_BNE TOKEN_REG TOKEN_COMMA TOKEN_REG TOKEN_COMMA spec_operand
			{ if (!ended) mk_branch(0x32, $2, $4, $6); free_op($6); }
		| TOKEN_BGT TOKEN_REG TOKEN_COMMA TOKEN_REG TOKEN_COMMA spec_operand
			{ if (!ended) mk_branch(0x33, $2, $4, $6); free_op($6); }
		| TOKEN_PUSH TOKEN_REG
			{ if (!ended) mk_push($2); }
		| TOKEN_POP TOKEN_REG
			{ if (!ended) mk_pop($2); }
		| TOKEN_XCHG TOKEN_REG TOKEN_COMMA TOKEN_REG
			{ if (!ended) mk_op(0x40, 0, $2, $4); }
		; */

		/* | TOKEN_IDENT {
			$$ = operand(MEM_SYM, 0, $1, 0);
		}
		| TOKEN_DOLLAR TOKEN_NUM{
			$$ = operand(IMM_LIT, $2, 0, 0);
		}
		| TOKEN_DOLLAR TOKEN_IDENT{
			$$ = operand(IMM_SYM, 0, $2, 0);
		}
		| TOKEN_REG {
			$$ = operand(IMM_REG, 0, 0, $1);
		}
		| TOKEN_LBRACKET TOKEN_REG TOKEN_RBRACKET {
			$$ = operand(MEM_REG, 0, 0, $2);
		}
		| TOKEN_LBRACKET TOKEN_REG TOKEN_PLUS TOKEN_NUM TOKEN_RBRACKET {
			$$ = operand(MEM_REG_LIT, $4, 0, $2);
		}
		| TOKEN_LBRACKET TOKEN_REG TOKEN_PLUS TOKEN_IDENT TOKEN_RBRACKET {
			$$ = operand(MEM_REG_SYM, 0, $4, $2);
		}
		;  */

	/* spec_operand
		: TOKEN_NUM {
			$$ = operand(IMM_LIT, $1, 0, 0);}
		| TOKEN_IDENT {
			$$ = operand(IMM_SYM, 0, $1, 0);
		}
		; */

sys_reg
    : TOKEN_STATUS   { $$ = $1; }
    | TOKEN_HANDLER  { $$ = $1; }
    | TOKEN_CAUSE    { $$ = $1; }
    ;


	%%

	int main() {


	FILE *file = fopen("src/test.s", "r");
		if(!file) printf("couldnt open file");

		yyin = file;

		do {
			yyparse();
		} while(!feof(yyin) && !ass_end);

	Assembler::end_last_section();
	Assembler::write_section_context();
	Assembler::write_symbol_table_context();
	Assembler::write_memory_content();

	fclose(file);


		return 0;
	}

	void yyerror(const char* s) {
		fprintf(stderr, "Parse error at line %d:\n", line_number);
		exit(1);
	}