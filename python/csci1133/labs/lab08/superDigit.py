def superDigit(n):
    if len(str(n)) == 1:
        return n
    else:
        n = int(str(n)[0]) + superDigit(int(str(n)[1:]))
        return superDigit(n)

print(superDigit(123456))