import numbers

def deepSquare(mylist):
    if mylist == []:
        return []
    elif isinstance(mylist[0], list):
        return [deepSquare(mylist[0])] + deepSquare(mylist[1:])
    elif isinstance(mylist[0], numbers.Number):
        return [mylist[0]**2] + deepSquare(mylist[1:])
    else:
        return deepSquare(mylist[1:])

print(deepSquare([2 , [3] , [4 , [5]] , 'b']))
