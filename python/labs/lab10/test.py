class rational:

    def __init__(self, num=0, den=1):
        self.numerator = num

        if den == 0:
            self.denominator = 1
        
        else:
            self.denominator = den
    
    def __str__(self):
        if self.numerator >= self.denominator:

            if self.numerator % self.denominator != 0:
                return str(self.numerator) + '/' + str(self.denominator)
        
            else:
                return str(int(self.numerator / self.denominator))
        
        else: 
            return str(self.numerator) + '/' + str(self.denominator)
    
    def scale(self, n):
        new_num = self.numerator * n
        new_dem = self.denominator * n
        return rational(new_num, new_dem)


num1 = rational(4,4)
num2 = rational(1,3)
num3 = rational()

print(num2.scale(3))