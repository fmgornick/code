### dodiv_segfault.s: provides a division function which computes 
### both quotient and remainder.
### 
### This version has a memory problem in it which
### leads to a segmentation fault.
### 
### int dodiv(int numer, int denom, int *quot, int *rem);        
### args:         1:edi      2:esi       3:rdx     4:rcx
	.text
	.global	dodiv
dodiv:
	cmpl $0,%edi            # compare arg1 to 0
        je .ERROR_ZERO

        movl %edi,%eax          # copy arg1 to eax for division
        cqto                    # set up division by copy to edx
        idivl %esi              # divide by arg2, eax has quot, edx has rem
        movl %eax,(%rdx)        # write quot to arg3
        movl %edx,(%rcx)        # write rem  to arg4
        movl $0,%eax            # return 0 on success
	ret                     
	
.ERROR_ZERO:
        movl $1,%eax            # return 1 on failure
        ret

