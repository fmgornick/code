import random
import math
def estimatePi():
	sampleSize = int(input('how many iterations? '))
	n = 1
	h = 0
	while(n <= sampleSize):
		x = random.uniform(-1,1)
		y = random.uniform(-1,1)
		r = math.sqrt((x)**2 + (y)**2)
		if r <= 1:
			h += 1
			n += 1
		else:
			n += 1
	p = h / sampleSize
	piest = 4*p
	print(piest)

estimatePi()
