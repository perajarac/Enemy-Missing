#PROBA SVIH DIREKTIVA
.global a, b, c
.extern d, e, f
.section g

#PROBA SVIH OPERACIJA

halt
int
add %r1, %r3
sub %r1, %r3
mul %r1, %r3
div %r4, %r8
not %r1
and %r1, %r3
or %r1, %r3
xor %r1, %r3
shl %r1, %r3
shr %r1, %r3
xchg %r1, %r2
csrrd %status, %r4
csrrd %handler, %r11
csrrd %cause, %r3
csrwr %r3, %status
csrwr %r11, %handler
csrwr %r3, %cause
; iret
; call 0x1
; call 1
; call symbol
; ret
; jmp 0x1
; jmp 1
; jmp symbol
; beq %r1, %sp, 0x1
; beq %r1, %sp, 1
; beq %r1, %sp, symbol
; bne %r1, %sp, 0x1
; bne %r1, %sp, 1
; bne %r1, %sp, symbol
; bgt %r1, %sp, 0x1
; bgt %r1, %sp, 1
; bgt %r1, %sp, symbol
; push %pc
; pop %r12
; ld $1, %r9
; ld $0x1, %r9
; ld $symbol, %r9
; ld 1, %r9
; ld 0x1, %r9
; ld symbol, %r9
; ld %r2, %r9
; ld [%r1], %r9
; ld [%r1 + 1], %r9
; ld [%r1 + 0x1], %r9
; st %r10, %r2
; st %r10, [%r1]
; st %r10, [%r1 + 1]
; st %r10, [%r1 + 0x1]
; csrrd %handler, %r4
; csrwr %r4, %status
; csrrd %handler, %r4
; csrwr %r4, %status
; .end