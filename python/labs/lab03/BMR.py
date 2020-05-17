print('this program gives the number of 230 calorie chocolate bars you would need to eat to maintain your weight without working out')

weight = int(input('what is your weight? (in lbs): '))
height = int(input('what is your height? (in inches): '))
age = int(input('what is your age? (in years): '))

repeat = True
while(repeat):
	gender = input('Are you male or female? (M for male F for female): ')
	if gender == str('M'):
		BMR = 66 + (6.3 * weight) + (12.9 * height) - (6.8 * age)
		bars = BMR // 230
		print('you would need to eat', int(bars), 'chocolate bars to maintain your weight')
		repeat = False
        
	elif gender == str('F'):
		BMR = 655 + (4.3 * weight) + (4.7 * height) - (4.7 * age)
		bars = BMR // 230
		print('you would need to eat', int(bars), 'chocolate bars to maintain your weight')
		repeat = False
        
	else:
		print('make sure you either type "M" for male or "F" for female')
		repeat = True
