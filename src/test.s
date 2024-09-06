.word b
.global a
.extern d
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
a:
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
ld $f, %r5
.skip 10
m:
ld 0xabc, %r5
ld f, %r5
st %r3, [%r1+f]
.word f
csrwr %r11, %handler
csrwr %r3, %cause