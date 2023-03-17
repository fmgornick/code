# CSCI 1133, Fletcher Gornick, gorni025
# lab Section 002, HW 5

#==========================================
# Name: cnt_occur

# Purpose: Take in a list of various types, and return the number of integers in
# the list 

# Precondition: The list will contain numerous types, return a 0 if the list is
# empty.  No using loops or iterative functions to count 

# Input Parameter(s): One list of integers, floats, strings, or lists

# Return Value(s): Returns the number of integers in the list, including integers 
# in embedded lists
#==========================================

def cnt_occur(mylist):
    if mylist == []:
        return 0
    elif isinstance(mylist[0], int):
        return 1 + cnt_occur(mylist[1:])
    elif isinstance(mylist[0], list):
        return cnt_occur(mylist[0]) + cnt_occur(mylist[1:])
    else:
        return cnt_occur(mylist[1:])





#==========================================
# Name: not_position

# Purpose: Taking in a list of integers, with another integer, it checks to see if
# the second parameter (integer) is equal to each position on the list.  If not,
# it adds that index position to another list and finally returns that list 

# Precondition: Assume that there, are no embedded lists, and that two parameters
# are 1: a list of only integers, and 2: an integer 

# Input Parameter(s): 
# 1. a list of integers
# 2. an integer

# Return Value(s): A list containing the index positions of all the values that
# aren't equal to the integer parameter 
#==========================================

def helper(mylist, num, count):
    if count >= len(mylist):
        return []
    elif mylist[count] != num:
        return [count] + helper(mylist, num, count + 1)
    else:
        return helper(mylist, num, count + 1)

def not_position(mylist, num):
    return helper(mylist, num, 0)





#==========================================
# Name: seq_of_mult_3

# Purpose: Finds the nth value of the sequence {2, 6, 18, 54, 162 ...}

# Precondition: Input parameter must be an integer greater than or equal to 1

# Input Parameter(s): Integer greater than or equal to 1

# Return Value(s): The nth value of the sequence (n is the input)
#==========================================

def sequence_of_mult_3(n):
    if n == 1:
        return 2
    elif n > 1:
        return 3 * sequence_of_mult_3(n-1)
    else:
        return 'not possible'





#==========================================
# Name: create_range

# Purpose: Takes in two integers, and creates a list ranging from one to the other

# Precondition: Both parameters must be integers and the first value must be less
# than or equal to the second (not in mine tho) 

# Input Parameter(s):
# 1. smaller value (integer)
# 2. larger value (integer)

# Return Value(s): A list of every integer in between the two inputs, including the
# inputs themselves
#==========================================

def create_range(a,b):
    if a == b:
        return [a]
    elif a < b:
        return [a] + create_range(a + 1,b)
    else:
        return [a] + create_range(a - 1,b)
