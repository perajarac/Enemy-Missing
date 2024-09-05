#PROBA SVIH DIREKTIVA
.global b, c
.extern d, e, f
.section g
#PROBA SVIH OPERACIJA
halt


.section a
a:
ld 0xabcd, %r5
a:
st %r2, 0xabc
st %r4,[%r3]