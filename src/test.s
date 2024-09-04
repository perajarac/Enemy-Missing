#PROBA SVIH DIREKTIVA
.word b
.global a, b, c
.extern d, e, f
.section g

#PROBA SVIH OPERACIJA
halt


.section a
ld 0xabcd, %r5
st %r2, 0xabc
st [%r3], %r4