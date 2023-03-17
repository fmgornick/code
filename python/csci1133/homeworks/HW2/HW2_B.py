# CSCI 1133, Lab Section 002, HW 2, Problem B
# FLETCHER_GORNICK, GORNI025

pounds = int(input('Weight in pounds:  '))
inches = int(input('Height in inches:  '))
age = int(input('Age:  '))

gloop = True
while(gloop):
    gender = input('Gender:  ')
    if gender == 'm':
        gloop = False
    elif gender == 'f':
        gloop = False
    else:
        print(gender, 'is not a gender, type either m or f')
        gloop = True

def convert_pounds_to_kg(pounds):
    weight = pounds * 0.453592
    return weight
weight = convert_pounds_to_kg(pounds)

def convert_inches_to_cm(inches):
    height = inches * 2.54
    return height
height = convert_inches_to_cm(inches)

def h_and_b(weight, height, age, gender):
    if gender == 'm':
        HBBMR = 66.5 + (13.75 * weight) + (5.003 * height) - (6.755 * age)
        return HBBMR
    elif gender == 'f':
         HBBMR = 655.1 + (9.563 * weight) + (1.850 * height) - (4.676 * age)
         return HBBMR

def r_and_s(weight, height, age, gender):
    if gender == 'm':
        RSBMR = 88.362 + (13.397 * weight) + (4.799 * height) - (5.677 * age)
        return RSBMR
    elif gender == 'f':
         RSBMR = 447.593 + (9.247 * weight) + (3.098 * height) - (4.330 * age)
         return RSBMR

def m_and_s(weight, height, age, gender):
    if gender == 'm':
        MSBMR = (10 * weight) + (6.25 * height) - (5 * age) + 5
        return MSBMR
    elif gender == 'f':
         MSBMR = (10 * weight) + (6.25 * height) - (5 * age) - 161
         return MSBMR

def main():
    print('Your weight in kilograms: ' , convert_pounds_to_kg(pounds))
    print('Your height in centimeters: ' , convert_inches_to_cm(inches))
    print('Harris and Benedict BMR: ' , h_and_b(weight, height, age, gender))
    print('Roza and Shizgal BMR: ' , r_and_s(weight, height, age, gender))
    print('Mifflin and St Jeor BMR: ' , m_and_s(weight, height, age, gender))

main()
