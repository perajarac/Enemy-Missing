%{
#include <string.h>

int yyparse(void);
int yylex(void);
void yyerror(const char*);
%}

%union {
    int num;
	int op_code;
    char* c;
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




%%

%%