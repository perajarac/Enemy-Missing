.word b
.global a
.extern d
.section g

#PROBA SVIH OPERACIJA
halt

int
add %pc, %r3
iret
pop %r2
push %r2
call 0xabcd
push %r2
f:
jmp f
ret