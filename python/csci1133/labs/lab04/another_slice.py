import math
tolerance = float(input('how close do you want it? '))

old = 6 / (math.sqrt(3))

n = 1
lp = True
while(lp):
    new = (6 / (math.sqrt(3))) * (1 + ((-1)**(n)) / ((3**n) * (2 * n + 1)))
    difference = math.fabs(new - old)
    if difference < tolerance:
        print('pi estimate is ', new, ', and we did ', n, 'iterations')
        lp = False
    else:
        old = new
        n += 1
        new = (6 / (math.sqrt(3))) * (1 + ((-1)**(n)) / ((3**n)*(2 * n + 1)))
        lp = True
