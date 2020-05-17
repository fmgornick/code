# CSCI 1133, Lab Section 002, HW 2, Problem A1
# FLETCHER_GORNICK, GORNI025

def subtractWhile(total, num, times):
    n = 1
    while n <= times:
        total -= num
        n += 1
    return total

def main():
    total = int(input('Please enter the current total:  '))
    num = int(input('What number will be subtracted?  '))
    times = int(input('How many times should we subtract?  '))

    print('Answer: ', total , '-', '(', num , '*', times , ') = ', end= '')
    print(subtractWhile(total, num, times))

main()
