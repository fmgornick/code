### int posneg(int *ptr);
### // Determines if pointer to given int has a positive or
### // negative value. Returns 0 for positive, 1 for negative.
### // Defined in posneg.s assembly file. 
### FIX BUGS IN THIS VERSION
.text
.global posneg
posneg:
        movq    (%rdi),%rsi
        cmpl    $0,%esi
        jl      .NEG
        movl    $0,%eax
        ret
.NEG:
        movl    $1,%eax
        ret

