#ifndef _assembler_hpp_
#define _assembler_hpp_

//tabelea simbola, tabela sekcija, relokaciona tabela

class Assembler{
public:
    enum instruction_codes {
        HALT_CODE = 1, INT_CODE, IRET_CODE, CALL_CODE, RET_CODE,JMP_CODE, BEQ_CODE, BNE_CODE, BGT_CODE,
        PUSH_CODE, POP_CODE, XCHG_CODE, ADD_CODE, SUB_CODE, MUL_CODE, DIV_CODE,
        NOT_CODE, AND_CODE, OR_CODE, XOR_CODE, SHL_CODE, SHR_CODE,
        LD_CODE, ST_CODE, CSRRD_CODE, CSRWR_CODE
    };
};

#endif