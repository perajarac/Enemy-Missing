# file: isr_timer.s
.global g
.section isr
# prekidna rutina za tajmer
.global isr_timer
isr_timer:
    st %r2, g # term_out

    ret

.end
