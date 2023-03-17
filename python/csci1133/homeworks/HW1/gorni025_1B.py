# CSCI 1133, Lab Section 002, HW 1, Problem 1B
# FLETCHER_GORNICK, GORNI025

print("This program converts fahrenheit temperatures to celsius and kelvin") 
print("Please enter the temperature in Fahrenheit: " , end= input())

f = float(input())
c = ((f - 32) * 5) / 9
k = c + 273.15

print("The temperature in Celsius is: " , c)
print("The temperature in Kelvin is: " , k)

if -459.67 < f <= 10:
    print("It is freezing out!")
elif 10 < f <= 32:
    print("It is cold!")
elif 32 < f <= 50:
    print("It is a bit chilly out")
elif 50 < f < 69:
    print("It is pretty temperate!")
elif f == 69:
    print("niceeeeeeee")
elif 69 < f <= 75:
    print("It is pretty temperate!")
elif 75 < f <= 90:
    print("It is hot!")
elif 90 < f:
    print("It is scorching!")
else:
    print("that's below absolute zero bud, that aint even possible!")
