class measure:

    def __init__(self, feet=0, inches=0):
        self.feet = feet
        self.inches = inches
        tf = True
        while(tf):
            if self.inches >= 12:
                self.inches -= 12
                self.feet += 1
                tf = True
            else:
                tf = False

    def __str__(self):
        return str(self.feet) + "'" + str(self.inches) + '"'
    
    def __add__(self, other):
        new_feet = self.feet + other.feet
        new_inches = self.inches + other.inches
        return measure(new_feet, new_inches)

    def __sub__(self, other):
        new_feet = self.feet - other.feet
        new_inches = self.inches - other.inches
        if new_inches < 0:
            return 'negative height'
        return measure(new_feet, new_inches)

