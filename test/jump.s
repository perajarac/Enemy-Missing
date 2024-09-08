.extern a, b
.global c

.section g
beq %r7, %r8, c
c:
jmp c
beq %r1, %r2, c
beq %r3, %r4, a
beq %r5, %r6, b
st %r1, c

