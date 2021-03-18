### Call the inc_larger function several times on variables in
### main. The main function has stack problems which must be
### fixed.

.text
.globl	main
main:
	subq	$16, %rsp

	movl	$2,  0(%rsp)
	movl	$3,  4(%rsp)
	movl	$6,  8(%rsp)
	movl	$7, 12(%rsp)
	
	leaq    0(%rsp), %rdi
	leaq    4(%rsp), %rsi
        call    inc_larger
	
	leaq     8(%rsp), %rdi
	leaq    12(%rsp), %rsi
        call    inc_larger
	
	leaq	.FORMAT1(%rip), %rdi   # arg1 .FORMAT1
	movl	 0(%rsp), %esi         # arg2
	movl	 4(%rsp), %edx         # arg3
	movl	 8(%rsp), %ecx         # arg4
	movl    12(%rsp), %r8d         # arg5
	movl	$0, %eax               # special setup for printf
	call	printf@PLT             # function call

	leaq	.FORMAT2(%rip), %rdi   # arg1 .FORMAT1
	movl	$0, %eax               # special setup for printf
	call	printf@PLT             # function call
	

		addq	$16, %rsp
        movl    $0,%eax
        ret
	
.global inc_larger
inc_larger:     
	movl    (%rdi), %edx
        movl    (%rsi), %ecx
        cmpl    %ecx, %edx
        jl      .INC_SECOND
        addl    $1,(%rdi)
        ret

.INC_SECOND:
        addl    $1,(%rsi)
        ret

.data
.FORMAT1:                       # format strings for printf calls
	.string	"%d, %d, %d, %d, who do we appreciate?\n"
.FORMAT2:	
	.string	"Compilers! Compilers! Yeeeeaaah COMPILERS!\n"
                
