f = int(input("enter a positive 4 digit number:  "))
f
a = f // 1000
b = (f - 1000 * a) // 100
c = (f - 1000 * a - 100 * b) // 10
d = f - 1000 * a - 100 * b - c * 10
print(a)
print(b)
print(c)
print(d)
