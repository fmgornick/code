def expo(x,y):
    loop = 1
    num = 0
    for i in range(y):
        for j in range(loop):
            num += x
        loop = num
        num = 0
    return loop

print(expo(2,5))
