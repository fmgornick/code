.text
.global col_check
col_check:
	movl	%edi,%r8d
	sarq	$32,%rdi
	movl	%edi,%r9d
	movl	$0,%r10d

	cmpl	$0,%r8d
	jle		.BIT_ONE

	.CHECK_2:
	cmpl	$0,%r9d
	jl		.BIT_TWO

	.CHECK_3_P1:
	cmpl	$1,%r8d
	je		.CHECK_3_P2
	jmp		.RET

	.CHECK_3_P2:
	cmpl	$0,%r9d
	jl		.BIT_THREE
	jmp		.RET

	.BIT_ONE:
	orl		$1,%r10d
	jmp .CHECK_2

	.BIT_TWO:
	orl		$2,%r10d
	jmp		.CHECK_3_P1

	.BIT_THREE:
	orl		$4,%r10d

	.RET:
	movl	%r10d,%eax
	ret
