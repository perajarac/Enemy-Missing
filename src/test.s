#PROBA SVIH DIREKTIVA
.word b
.global a, b, c
.extern d, e, f
.section g

#PROBA SVIH OPERACIJA
halt

int
add %pc, %r3
sub %r1, %r3
mul %r1, %r3
div %r4, %r8
.section a
.word m
not %r1
and %r1, %r3
or %r1, %r3
xor %r1, %r3
shl %r1, %r3
shr %r1, %r3
.section b
xchg %r1, %r2
csrrd %status, %r4
csrrd %handler, %r11
csrrd %cause, %r3
csrwr %r3, %status
ld [%r1 + 0xa], %r4
.section g
.skip 10
ld [%r1 + 0xabcd], %r5
.word f
csrwr %r11, %handler
csrwr %r3, %cause