class vector:

    def __init__(self, vlist=[0,0,0]):
        self.vlist = vlist
    
    def __str__(self):
        return str(self.vlist)
    
    def getValues(self):
        return self.vlist
    
    def setValues(self, new_vlist):
        self.vlist = new_vlist
    
    def magnitude(self):
        return sum(self.vlist)
    
    def __add__(self, other):

        new_list = []
        if len(self.vlist) < len(other.vlist):

            for i in range(0, len(self.vlist)):
                new_list.append(self.vlist[i] + other.vlist[i])
            
            for i in range(len(self.vlist), len(other.vlist)):
                new_list.append(other.vlist[i])
        
        elif len(self.vlist) >= len(other.vlist):

            for i in range(0, len(other.vlist)):
                new_list.append(self.vlist[i] + other.vlist[i])
        
        return new_list
    
    def __mul__(self,num):
        for i in range(len(self.vlist)):
            self.vlist[i] *= num
        return self.vlist
            
