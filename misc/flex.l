%{
#include <iostream>
#include "../misc/parser.hpp"
using namespace std;
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

%%
{global} { return (TOKEN_GLOBAL); }
{extern} { return (TOKEN_EXTERN); }
{section} { return (TOKEN_SECTION); }
{word} { return (TOKEN_WORD); }
{skip} { return (TOKEN_SKIP); }
{ascii} { return (TOKEN_ASCII); }
{end}   { return (TOKEN_END); }

{halt} {yylval.opcode = HALT_CODE; return (TOKEN_HALT); }
{int}  {yylval.opcode = INT_CODE; return (TOKEN_INT); }
{iret} {yylval.opcode = IRET_CODE; return (TOKEN_IRET); }
{call} {yylval.opcode = CALL_CODE; return (TOKEN_CALL); }
{ret} {yylval.opcode = RET_CODE; return (TOKEN_RET); }
{jmp} {yylval.opcode = JMP_CODE; return (TOKEN_JMP); }
{beq} {yylval.opcode = BEQ_CODE; return (TOKEN_BEQ); }
{bne} {yylval.opcode = BNE_CODE; return (TOKEN_BNE); }
{bgt} {yylval.opcode = BGT_CODE; return (TOKEN_BGT); }
{push} {yylval.opcode = PUSH_CODE; return (TOKEN_PUSH); }
{pop} {yylval.opcode = POP_CODE; return (TOKEN_POP); }
{xchg} {yylval.opcode = XCHG_CODE; return (TOKEN_XCHG); }
{add} {yylval.opcode = ADD_CODE; return (TOKEN_ADD); }
{sub} {yylval.opcode = SUB_CODE; return (TOKEN_SUB); }
{mul} {yylval.opcode = MUL_CODE; return (TOKEN_MUL); }
{div} {yylval.opcode = DIV_CODE; return (TOKEN_DIV); }
{not} {yylval.opcode = NOT_CODE; return (TOKEN_NOT); }
{and} {yylval.opcode = AND_CODE; return (TOKEN_AND); }
{or} {yylval.opcode = OR_CODE; return (TOKEN_OR); }
{xor} {yylval.opcode = XOR_CODE; return (TOKEN_XOR); }
{shl} {yylval.opcode = SHL_CODE; return (TOKEN_SHL); }
{shr} {yylval.opcode = SHR_CODE; return (TOKEN_SHR); }
{ld} {yylval.opcode = LD_CODE; return (TOKEN_LD); }
{st} {yylval.opcode = ST_CODE; return (TOKEN_ST); }
{csrrd} {yylval.opcode = CSRRD_CODE; return (TOKEN_CSRRD); }
{csrwr} {yylval.opcode = CSRWR_CODE; return (TOKEN_CSRWR); }

/* {gpr} {yylval.reg = getNums(yytext); return (TOKEN_GPR); }
{sp} {yylval.reg = SP_CODE; return (TOKEN_GPR); }
{pc} {yylval.reg = PC_CODE; return (TOKEN_GPR); }
{sstatus} {yylval.reg = STATUS_CODE; return (TOKEN_STATUS); }
{handler} {yylval.reg = HANDLER_CODE; return (TOKEN_HANDLER); }
{cause} {yylval.reg = CAUSE_CODE; return (TOKEN_CAUSE); } */

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
{enter} { line_number++; }

{string} { yylval.ident = strdup(yytext); return TOKEN_STRING; }
{digit} { yylval.num = atoi(yytext); return TOKEN_NUM; }
{hex} { yylval.num = strtoq(yytext, NULL, 16); return TOKEN_NUM; }

%%


int main(){
    yylex();
    return 0;
}