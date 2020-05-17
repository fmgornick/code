names = ['joe', 'tom', 'barb', 'sue','sally']
scores = [11, 22, 14, 17, 10]

def makeDictionary(list1, list2):
    scoreDict = {k : v for k, v in zip(list1, list2)}
    return scoreDict

scoreDict = {k : v for k, v in zip(names, scores)}


scoreDict['john'] = 18


def average_mydict(mydict):
    sum = 0
    n = 0
    for k in mydict:
        sum += mydict[k]
        n += 1
    return sum / n

del scoreDict['tom']

scoreDict['sally'] = 15

def getScore(mydict, name):
    if name in mydict:
        return mydict[name]
    else:
        return -1

