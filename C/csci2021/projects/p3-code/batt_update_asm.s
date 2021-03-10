.text
.global  set_batt_from_ports
set_batt_from_ports:
    ## int set_batt_from_ports(batt_t *batt)
    ## args                         1: rdi

    # set rax register equal to BATT_VOLTAGE_PORT global variable
    movw    BATT_VOLTAGE_PORT(%rip), %ax
    # return 1 if negative
    cmpw    $0, %ax
    jl  .ERROR_NEGATIVE

    # calculate batt->mlvolts
    movw    $2, %r8w
    cqto
    idivw   %r8w
    movw    %ax, (%rdi)

    # calculate batt->percent
    subw    $3000, %ax
    movw    $8, %r8w
    cwtl
    cltq
    cqto
    idivw   %r8w

    # check if percent is outside of 0-100 range
    cmpw    $0, %ax
    jl  .PERCENT_LOW
    cmpw    $100, %ax
    jg  .PERCENT_HIGH

    # set percentage
    movb    %al, 2(%rdi)
    jmp .MODE_SET

    # if percentage < 0
    .PERCENT_LOW:
        movb    $0, 2(%rdi)
        jmp     .MODE_SET

    # if percentage > 100
    .PERCENT_HIGH:
        movb    $100, 2(%rdi)

    # set batt->mode
    .MODE_SET:
        movb    BATT_STATUS_PORT(%rip), %al
        andb    $4, %al
        sarb    $2, %al
        addb    $1, %al
        movb    %al, 3(%rdi)

    movl    $0, %eax
    ret

    # return 1 conditional
    .ERROR_NEGATIVE:
        movl    $1, %eax
        ret

# change to definint semi-global variables used with the next function 
# via the '.data' directive
.data
pattern:
    .int    63
    .int    6
    .int    91
    .int    79
    .int    102
    .int    109
    .int    125
    .int    7
    .int    127
    .int    111

.text
.global  set_display_from_batt


set_display_from_batt:  
    # int set_display_from_batt(batt_t batt, int *display)
    # args:                         1: edi      2: rsi

    # must push callee-save registers onto the stack
    pushq   %r12
    pushq   %r13
    pushq   %r14
    # load pointer to bit sequence array
    leaq    pattern(%rip), %r8
    # load batt into register
    movl    %edi, %r9d
    # load display batt pointer into register
    movq    %rsi, %r10

    # conditional check batt->mode
    sarl    $24, %r9d
    cmpb    $1, %r9b
        je      .MODE_ONE
    cmpb    $2, %r9b
        je      .MODE_TWO

    # if mode != 1 or 2 then return 1
    jmp     .ERROR_MODE

    .MODE_ONE:
        # shift r9 register back to original declared position
        movl    %edi, %r9d
        # initialize mask
        movl    $3, %r11d
        sall    $22, %r11d

        # set ax register to volts (divide mlvolts by 10)
        movw    %r9w, %ax
        cqto
        movw    $10, %r12w
        idivw   %r12w

        cmpw    $5, %dx
        jge     .ROUND_UP
        jmp     .NO_ROUND_UP

        # round up by one if .5 or greater
        .ROUND_UP:
            addw    $1, %ax

        .NO_ROUND_UP:
        movb    $0, %r13b
        # for (int i=0; i<3; i++)
        .FOR_LOOP_MODE_1:
            # int divide voltage by 10
            cqto
            movb    $10, %r12b
            idivw   %r12w
            # r14 register is the number it needs to be shifted
            movb    %r13b, %r14b
            imull   $7, %r14d
            # change r12 register to number bit representation
            movl    (%r8, %rdx, 4), %r12d
            # shift bits to correct position
            movb    %r14b, %cl
            sall    %cl, %r12d
            # change the mask to include the bits
            orl     %r12d, %r11d
            # increment i
            addb    $1, %r13b
            # compare i to 3
            cmpb    $3, %r13b
            jl      .FOR_LOOP_MODE_1

        # jump to battery indicator
        jmp     .BATTERY

    .MODE_TWO:
        # shift r9 register back to original declared position
        movl    %edi, %r9d
        # initialize mask
        movl    $1, %r11d
        sall    $21, %r11d

        # set al register to batt->percent
        movl    %edi, %r9d
        sarl    $16, %r9d
        movl    $0, %eax
        movb    %r9b, %al

        movb    $0, %r13b
        # for (int i=0; i<3; i++)
        .FOR_LOOP_MODE_2:
            # int divide percent by 10
            cqto
            movl    $10, %r12d
            idivl   %r12d
            # r14 register is the number it needs to be shifted
            movl    %r13d, %r14d
            imull   $7, %r14d
            # change r12 register to number bit representation
            movl    (%r8, %rdx, 4), %r12d
            # shift bits to correct position
            movb    %r14b, %cl
            sall    %cl, %r12d
            # change the mask to include the bits
            orl     %r12d, %r11d
            # increment i
            addb    $1, %r13b
            # compare i to 3
            cmpb    $3, %r13b
            jl      .FOR_LOOP_MODE_2

        # check if percentage is less than 100
        cmpb    $100, %r9b
        jl      .TWO_DIGIT
        jmp     .BATTERY

        # check if percentage is less than 10
        .ONE_DIGIT_CHECK:
        cmpb    $10, %r9b
        jl      .ONE_DIGIT
        jmp     .BATTERY

        # if less than 100, drop a zero
        .TWO_DIGIT:
            # create a bit sequence that's the inverse of a zero and & it 
            # with mask at a certain shifted location
            movl    (%r8), %r12d
            movb    $14, %cl
            sall    %cl, %r12d
            notl    %r12d
            andl    %r12d, %r11d
            jmp     .ONE_DIGIT_CHECK

        # if less than 100, drop another zero
        .ONE_DIGIT:
            # create a bit sequence that's the inverse of a zero and & it 
            # with mask at a certain shifted location
            movl    (%r8), %r12d
            movb    $7, %cl
            sall    %cl, %r12d
            notl    %r12d
            andl    %r12d, %r11d


    # fill correct bars on battery
    .BATTERY:
        # set r9 register to percentage
        movl    %edi, %r9d
        sarl    $16, %r9d

        cmpb    $5, %r9b
        jge     .ONE_BAR
        jmp     .RET

        # this is all basically just a bunch of if statements
        .TWO_BARS_CHECK:
        cmpb    $30, %r9b
        jge     .TWO_BARS
        jmp     .RET

        .THREE_BARS_CHECK:
        cmpb    $50, %r9b
        jge     .THREE_BARS
        jmp     .RET

        .FOUR_BARS_CHECK:
        cmpb    $70, %r9b
        jge     .FOUR_BARS
        jmp     .RET

        .FIVE_BARS_CHECK:
        cmpb    $90, %r9b
        jge     .FIVE_BARS
        jmp     .RET

        .ONE_BAR:
            movb    $1, %r12b
            movb    $24, %cl
            sall    %cl, %r12d
            orl     %r12d, %r11d
            jmp     .TWO_BARS_CHECK

        .TWO_BARS:
            movb    $1, %r12b
            movb    $25, %cl
            sall    %cl, %r12d
            orl     %r12d, %r11d
            jmp     .THREE_BARS_CHECK

        .THREE_BARS:
            movb    $1, %r12b
            movb    $26, %cl
            sall    %cl, %r12d
            orl     %r12d, %r11d
            jmp     .FOUR_BARS_CHECK

        .FOUR_BARS:
            movb    $1, %r12b
            movb    $27, %cl
            sall    %cl, %r12d
            orl     %r12d, %r11d
            jmp     .FIVE_BARS_CHECK

        .FIVE_BARS:
            movb    $1, %r12b
            movb    $28, %cl
            sall    %cl, %r12d
            orl     %r12d, %r11d

    .RET:
        # free up callee-save registers
        popq    %r14
        popq    %r13
        popq    %r12
        movl    %r11d, (%rsi)
        movl    $0, %eax
        ret

    .ERROR_MODE:
        # free up callee-save registers
        popq    %r14
        popq    %r13
        popq    %r12
        movl    $0, %eax
        ret

.text
.global batt_update
        
batt_update:
    # initialize batt to all zeros
    pushq   $0
    # make argument 1 a pointer to batt
    movq    %rsp, %rdi
    call    set_batt_from_ports
    # check return value
    cmpl    $1, %eax
    # if set_batt_from_ports returns 1, then return 1
    je      .RETURN_ERROR

    # move batt struct into first argument
    movl    (%rsp), %edi
    # move poiner to batt struct into second argument
    movq    %rsp, %rsi
    call    set_display_from_batt
    # take the 8 byte number and drop it into r8 then increment the stack by 8
    popq    %r8
    # take first 4 bytes of r8 which is the batt struct and move them into the 
    # BATT_DISPLAY_PORT global variable
    movl    %r8d, BATT_DISPLAY_PORT(%rip)
    # make sure return value is 0
    movl    $0, %eax
    ret

    .RETURN_ERROR:
        popq    %r8
        ret
