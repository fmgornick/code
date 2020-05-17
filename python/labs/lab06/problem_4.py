def usingWhileLoop(randomlist):
    sortedlist = []
    ints = 0
    strs = 0
    other = 0
    i = 0
    while(i<len(randomlist)):
        if type(randomlist[i]) == int:
            ints += 1
        elif type(randomlist[i]) == str:
            strs +=1
        else:
            other += 1
        i += 1
    sortedlist.append(ints)
    sortedlist.append(strs)
    sortedlist.append(other)
    return sortedlist

print(usingWhileLoop([1,2,3,'cat','dag',3.0,[1,2]]))
