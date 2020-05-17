import random

num2 = 0
num3 = 0
num4 = 0
num5 = 0
num6 = 0
num7 = 0
num8 = 0
num9 = 0
num10 = 0
num11 = 0
num12 = 0
for i in range(1, 10001):
    dice1 = random.randint(1,6)
    dice2 = random.randint(1,6)

    if dice1 + dice2 == 2:
        num2 += 1
    elif dice1 + dice2 == 3:
        num3 += 1
    elif dice1 + dice2 == 4:
        num4 += 1
    elif dice1 + dice2 == 5:
        num5 += 1
    elif dice1 + dice2 == 6:
        num6 += 1
    elif dice1 + dice2 == 7:
        num7 += 1
    elif dice1 + dice2 == 8:
        num8 += 1
    elif dice1 + dice2 == 9:
        num9 += 1
    elif dice1 + dice2 == 10:
        num10 += 1
    elif dice1 + dice2 == 11:
        num11 += 1
    elif dice1 + dice2 == 12:
        num12 += 1

print('2: ', num2)
print('3: ', num3)
print('4: ', num4)
print('5: ', num5)
print('6: ', num6)
print('7: ', num7)
print('8: ', num8)
print('9: ', num9)
print('10: ', num10)
print('11: ', num11)
print('12: ', num12)
