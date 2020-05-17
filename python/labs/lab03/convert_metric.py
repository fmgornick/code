response = True
while(response):
    value = float(input('Enter value: '))
    unit = input('Enter units: ')

    if unit == 'pounds':
        convert = value * 0.453592
        print(convert, 'kilos')
        check = input('Do you wish to continue (y/n)? ')
        if check == 'n':
            response = False

    elif unit == 'kilos':
        convert = value * 2.20462
        print(convert, 'pounds')
        check = input('Do you wish to continue (y/n)? ')
        if check == 'n':
            response = False

    elif unit == 'ounces':
        convert = value * 28.3495
        print(convert, 'grams')
        check = input('Do you wish to continue (y/n)? ')
        if check == 'n':
            response = False

    elif unit == 'grams':
        convert = value * 0.035274
        print(convert, 'ounces')
        check = input('Do you wish to continue (y/n)? ')
        if check == 'n':
            response = False

    elif unit == 'miles':
        convert = value * 1.60934
        print(convert, 'kilometers')
        check = input('Do you wish to continue (y/n)? ')
        if check == 'n':
            response = False

    elif unit == 'kilometers':
        convert = value * 0.621371
        print(convert, 'miles')
        check = input('Do you wish to continue (y/n)? ')
        if check == 'n':
            response = False

    elif unit == 'inches':
        convert = value * 2.54
        print(convert, 'centimeters')
        check = input('Do you wish to continue (y/n)? ')
        if check == 'n':
            response = False

    elif unit == 'centimeters':
        convert = value * 0.393701
        print(convert, 'inches')
        check = input('Do you wish to continue (y/n)? ')
        if check == 'n':
            response = False

    else:
        print(value, unit, 'is not a valid unit')
        response = False
