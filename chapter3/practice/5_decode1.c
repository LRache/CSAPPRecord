/*
void decode1 (long *xp, long *yp, long *zp) 
xp in %rdi , yp in %rsi , zp in %rdx 
decode1: 
    movq (%rdi), %r8 
    movq (%rsi), %rcx 
    movq (%rdx), %rax 
    movq %r8, (%rsi) 
    movq %rcx, (%rdx) 
    movq %rax, (%rdi) 
    ret
*/

void decode1(long *xp, long *yp, long *zp) {
    long t_r8 = *xp; // r8
    long t_rcx = *yp; // rcx
    long t_rax = * zp; // rax
    *yp = t_r8;
    *zp = t_rcx;
    *xp = t_rax;
    return t_rax;
}