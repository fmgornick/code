import numbers

def deepSquare2(mylist):
    if mylist == []:
        return []
    elif isinstance(mylist[0], list):
        return deepSquare2(mylist[0]) + deepSquare2(mylist[1:])
    elif isinstance(mylist[0], numbers.Number):
        return [mylist[0]**2] + deepSquare2(mylist[1:])
    else:
        return deepSquare2(mylist[1:])


print(deepSquare2([2 , [3] , [4 , [5]] , 'b']))
