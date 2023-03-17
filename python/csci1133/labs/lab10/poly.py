class Poly:
    
    def __init__(self, coefficient=[0]):
        self.coefficient = coefficient
    
    def degree(self):
        return len(self.coefficient) - 1
    
    def insertTerm(self, exp, coef):

        tf = True
        while(tf):

            if len(self.coefficient) >= exp + 1:
                self.coefficient[exp] = coef
                tf = False
            
            else:
                self.coefficient.append(0)
                tf = True

    def __str__(self):

        final_string = ''
        bad_coefficients = [-1,0,1]
        bad_exponents = [0,1]

        for i in range(len(self.coefficient) - 1, -1, -1):

            value = ''

            if i == len(self.coefficient) - 1:
                if self.coefficient[i] not in bad_coefficients:
                    value = str(self.coefficient[i]) + 'x^' + str(i)
                elif self.coefficient[i] == -1:
                    value = '-x^' + str(i)
                elif self.coefficient[i] == 1:
                    value = 'x^' + str(i)
            
            elif i not in bad_exponents:
                if self.coefficient[i] not in bad_coefficients:

                    if self.coefficient[i] > 0:
                        value = ' + ' + str(self.coefficient[i]) + 'x^' + str(i)

                    else:
                        self.coefficient[i] = str(self.coefficient[i])[1:]
                        value = ' - ' + str(self.coefficient[i]) + 'x^' + str(i)
                    
                elif self.coefficient[i] == 1:
                    value = ' + x^' + str(i)
                
                elif self.coefficient[i] == -1:
                    value = ' - x^' + str(i)
            
            elif i == 1:
                if self.coefficient[i] not in bad_coefficients:

                    if self.coefficient[i] > 0:
                        value = ' + ' + str(self.coefficient[i]) + 'x'
                    
                    else:
                        self.coefficient[i] = str(self.coefficient[i])[1:]
                        value = ' - ' + str(self.coefficient[i]) + 'x'
            
            else:
                if self.coefficient[i] > 0:
                    value = ' + ' + str(self.coefficient[i])
                
                elif self.coefficient[i] < 0:
                    self.coefficient[i] = str(self.coefficient[i])[1:]
                    value = ' + ' + str(self.coefficient[i])



        
            final_string += value
        
        return final_string
    