def f_equals_c():
	c = 100
	lp = True
	while(lp and c > -40):
		f = (9 / 5)*(c) + 32
		if f <= c:
			print('f = c at ', c, 'degrees')
			lp = False
		else:
			print('c = ', c)
			print('f = ', f)
			c -= 1
			lp = True

def main():
	f_equals_c()

main()
