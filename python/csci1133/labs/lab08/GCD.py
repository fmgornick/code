def GCD(a,b):
    if b == 0:
        return a
    else:
        r = a % b
        return GCD(b,r)

print(GCD(1260,198))