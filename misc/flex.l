%{
#include <stdio.h>
#include "../inc/parser.hpp"
#include "../inc/assembler.hpp"
int line_number = 1;

%}

%option noyywrap

global ^\.global
extern ^\.extern
section ^\.section
word ^\.word
skip ^\.skip
ascii ^\.ascii
end	^\.end

halt halt
int int
iret iret
call call
ret ret
jmp jmp
beq beq
bne bne
bgt bgt
push push
pop pop
xchg xchg
add add
sub sub
mul mul
div div
not not
and and
or or
xor xor
shl shl
shr shr
ld ld
st st
csrrd csrrd
csrwr csrwr

comment #.*$
wspace \s*
string \"[a-zA-Z0-9_ ]*\"
enter \n
digit [0-9]
hex 0[xX][0-9a-fA-F]+
ident [a-zA-Z_][a-zA-Z0-9_]*

gpr (%r([0-9]|1[0-3]))
sp (%sp|%r14)
pc (%pc|%r15)
sstatus (%status)
handler (%handler)
cause (%cause)

lz \(
dz \)
lvz \[
dvz \]
plus \+
minus -
procenat %
dolar \$
tz ;
dt :
z ,
unknown .

%%
{global} { return (TOKEN_GLOBAL); }
{extern} { return (TOKEN_EXTERN); }
{section} { return (TOKEN_SECTION); }
{word} { return (TOKEN_WORD); }
{skip} { return (TOKEN_SKIP); }
{ascii} { return (TOKEN_ASCII); }
{end}   { return (TOKEN_END); }

{halt} {yylval.op_code = Assembler::instruction::HALT_CODE; return (TOKEN_HALT); }
{int}  {yylval.op_code = Assembler::instruction::INT_CODE; return (TOKEN_INT); }
{iret} {yylval.op_code = Assembler::instruction::IRET_CODE; return (TOKEN_IRET); }
{call} {yylval.op_code = Assembler::instruction::CALL_CODE; return (TOKEN_CALL); }
{ret} {yylval.op_code = Assembler::instruction::RET_CODE; return (TOKEN_RET); }
{jmp} {yylval.op_code = Assembler::instruction::JMP_CODE; return (TOKEN_JMP); }
{beq} {yylval.op_code = Assembler::instruction::BEQ_CODE; return (TOKEN_BEQ); }
{bne} {yylval.op_code = Assembler::instruction::BNE_CODE; return (TOKEN_BNE); }
{bgt} {yylval.op_code = Assembler::instruction::BGT_CODE; return (TOKEN_BGT); }
{push} {yylval.op_code = Assembler::instruction::PUSH_CODE; return (TOKEN_PUSH); }
{pop} {yylval.op_code = Assembler::instruction::POP_CODE; return (TOKEN_POP); }
{xchg} {yylval.op_code = Assembler::instruction::XCHG_CODE; return (TOKEN_XCHG); }
{add} {yylval.op_code = Assembler::instruction::ADD_CODE; return (TOKEN_ADD); }
{sub} {yylval.op_code = Assembler::instruction::SUB_CODE; return (TOKEN_SUB); }
{mul} {yylval.op_code = Assembler::instruction::MUL_CODE; return (TOKEN_MUL); }
{div} {yylval.op_code = Assembler::instruction::DIV_CODE; return (TOKEN_DIV); }
{not} {yylval.op_code = Assembler::instruction::NOT_CODE; return (TOKEN_NOT); }
{and} {yylval.op_code = Assembler::instruction::AND_CODE; return (TOKEN_AND); }
{or} {yylval.op_code = Assembler::instruction::OR_CODE; return (TOKEN_OR); }
{xor} {yylval.op_code = Assembler::instruction::XOR_CODE; return (TOKEN_XOR); }
{shl} {yylval.op_code = Assembler::instruction::SHL_CODE; return (TOKEN_SHL); }
{shr} {yylval.op_code = Assembler::instruction::SHR_CODE; return (TOKEN_SHR); }
{ld} {yylval.op_code = Assembler::instruction::LD_CODE; return (TOKEN_LD); }
{st} {yylval.op_code = Assembler::instruction::ST_CODE; return (TOKEN_ST); }
{csrrd} {yylval.op_code = Assembler::instruction::CSRRD_CODE; return (TOKEN_CSRRD); }
{csrwr} {yylval.op_code = Assembler::instruction::CSRWR_CODE; return (TOKEN_CSRWR); }


{lz}      { return (TOKEN_LPAR); }
{dz}      { return (TOKEN_RPAR); }
{lvz} { return (TOKEN_LBRACKET); }
{dvz} { return (TOKEN_RBRACKET); }
{plus}      { return (TOKEN_PLUS); }
{minus}  { return (TOKEN_MINUS); }
{procenat} { return (TOKEN_PERCENT); }
{dolar} { return (TOKEN_DOLLAR); }
{tz}      { return (TOKEN_SEMI); }
{dt} { return (TOKEN_COLON); }
{z}     { return (TOKEN_COMMA); }

{comment} { }
{wspace}        {  }
{enter} {line_number++; }
{ident} {return TOKEN_IDENT;}

{string} {yylval.ident = strdup(yytext); return TOKEN_STRING; }
{digit} {yylval.num = atoi(yytext); return TOKEN_NUM; }
{hex} {yylval.num = strtoq(yytext, NULL, 16); return TOKEN_NUM; }

{gpr} {yylval.num = atoi(yytext + 2); return TOKEN_REG;}
{sp} {yylval.num = 14; return TOKEN_SP;}
{pc} {yylval.num = 15; return TOKEN_PC;}

{sstatus} {yylval.ident = strdup(yytext); return TOKEN_STATUS;}
{handler} {yylval.ident = strdup(yytext); return TOKEN_HANDLER;}
{cause} {yylval.ident = strdup(yytext); return TOKEN_CAUSE;}

%%

