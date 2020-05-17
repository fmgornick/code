t = int(input("insert a temperature (degrees fahrenheit): "))
v = int(input("insert a wind velocity (miles per hour): "))
wc = 35.74 + 0.6215 * t - 35.75 * v**0.16 + 0.4275 * t * v**0.16
print("the windchill is... " , wc)
