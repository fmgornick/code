# CSCI 1133, Lab Section 002, HW 2, Problem A2
# FLETCHER_GORNICK, GORNI025

def subtractFor(total, num, times):
    for n in range(times):
        total -= num
    return total

def main():
    total = int(input('Please enter the current total:  '))
    num = int(input('What number will be subtracted?  '))
    times = int(input('How many times should we subtract?  '))

    print('Answer: ', total , '-', '(', num , '*', times , ') = ', end= '')
    print(subtractFor(total, num, times))

main()
