response = True
while(response):
    m = int(input('Enter month (number): '))
    d = int(input('Enter day: '))
    y = int(input('Enter year: '))

    if m == 1 or m == 2:
        m2 = m + 12
    elif 2 < m <= 12:
        m2 = m
    else:
        print(m, 'is not a valid month')
        response = False

    DoW = (d + 5 + (26 * (m2 + 1)) // 10 + (5 * (y % 100)) // 4 + (21 * (y // 100)) // 4) % 7
    
    if DoW == 0:
        print(m,'/',d,'/',y, 'is a Monday')
        check = input('Do you wish to continue (y/n)? ')
        if check == 'n':
            response = False

    elif DoW == 1:
        print(m,'/',d,'/',y, 'is a Tuesday')
        check = input('Do you wish to continue (y/n)? ')
        if check == 'n':
            response = False

    elif DoW == 2:
        print(m,'/',d,'/',y, 'is a Wednesday')
        check = input('Do you wish to continue (y/n)? ')
        if check == 'n':
            response = False

    elif DoW == 3:
        print(m,'/',d,'/',y, 'is a Thursday')
        check = input('Do you wish to continue (y/n)? ')
        if check == 'n':
            response = False

    elif DoW == 4:
        print(m,'/',d,'/',y, 'is a Friday')
        check = input('Do you wish to continue (y/n)? ')
        if check == 'n':
            response = False

    elif DoW == 5:
        print(m,'/',d,'/',y, 'is a Saturday')
        check = input('Do you wish to continue (y/n)? ')
        if check == 'n':
            response = False

    elif DoW == 6:
        print(m,'/',d,'/',y, 'is a Sunday')
        check = input('Do you wish to continue (y/n)? ')
        if check == 'n':
            response = False
    else:
        print('error')
        response = False
