import random
import turtle

def randColor():
    colors = ['red', 'yellow', 'gree', 'blue', 'purple', 'orange']
    return random.choice(colors)




class Shape:

    def __init__(self, x=0, y=0, color='', fill=False):
        self.x = x
        self.y = y
        self.color = color
        self.fill = fill

    def setFillColor(self, newcolor):
        self.color = newcoler
    
    def setFilled(self, bool):
        self.fill = bool
    
    def isFilled(self):
        return self.fill



