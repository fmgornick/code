# CSCI 1133, Lab Section 002, HW 2, Problem C
# FLETCHER_GORNICK, GORNI025

def forecast():
    yn = True
    while(yn):
        Q1 = input('Is the temperature greater than 70˚F?  ')
        if Q1 == 'yes':
            yn = False
        elif Q1 == 'no':
            yn = False
        else:
            print(Q1, 'is not correct spelling, please type "yes" or "no"...')
            yn = True

    if Q1 == 'yes':
        yn = True
        while(yn):
            Q2 = input('Is the wind greater than 2 mph?  ')
            if Q2 == 'yes':
                yn = False
            elif Q2 == 'no':
                yn = False
            else:
                print(Q2, 'is not correct spelling, please type "yes" or "no"...')
                yn = True

        if Q2 == 'yes':
            yn = True
            while(yn):
                Q4 = input('Is the atmospheric pressure greater than 26 inHg (inches of mercury)?  ')
                if Q4 == 'yes':
                    yn = False
                elif Q4 == 'no':
                    yn = False
                else:
                    print(Q4, 'is not correct spelling, please type "yes" or "no"...')
                    yn = True

            if Q4 == 'yes':
                print('rain')
            else:
                print('no rain')

        else:
            print('no rain')

    else:
        yn = True
        while(yn):
            Q3 = input('Is the wind greater than 4.5 mph?  ')
            if Q3 == 'yes':
                yn = False
            elif Q3 == 'no':
                yn = False
            else:
                print(Q3, 'is not correct spelling, please type "yes" or "no"...')
                yn = True

        if Q3 == 'yes':
            print('rain')

        else:
            yn = True
            while(yn):
                Q5 = input('Is the atmospheric pressure greater than 31 inHg (inches of mercury)?  ')
                if Q5 == 'yes':
                    yn = False
                elif Q5 == 'no':
                    yn = False
                else:
                    print(Q5, 'is not correct spelling, please type "yes" or "no"...')
                    yn = True

            if Q5 == 'yes':
                print('rain')
            else:
                print('no rain')

def main():
    forecast()

main()
