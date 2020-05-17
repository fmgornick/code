
def max_value_helper(mylist, n):
    if mylist == []:
        return n
    else:
        if mylist[0] > n:
            n = mylist[0]
        return max_value_helper(mylist[1:],n)

def maxValue(mylist):
    return max_value_helper(mylist, 0)

print(maxValue([1,2,3,4,3,7,5,6,8,10,3,2]))