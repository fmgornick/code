# CSCI 1133, Fletcher Gornick, gorni025
# lab Section 002, HW 4


#==========================================
# Name: remove_the_fact
# Purpose: Given a list of strings, create a new list that has in
# position 0 the number of times “fact” was in the original list and in
# position 1, a list of all other strings in the original list that were
# not “fact”. There can be duplication of strings on the new list.
# Precondition: The list will only contain strings.
# Input Parameter(s)
# my_list: a list containing only strings or the empty list
# Return Value(s)
# -- if the input parameter is an empty list, return a list
# of [0, []]
# -- else return a list with the 0th index position containing the
# number of times “fact” was seen on the list and the 1st
# index position containing the list of the strings that are
# not “fact”. If there are no strings on the list, return
# an empty list in that position.
#============================================

def remove_the_fact(my_list):

    n = 0
    new_list = []
    for i in my_list:

        if i == 'fact':
            n += 1
        else:
            new_list.append(i)

    return [n, new_list]






#==========================================
# Name: average_of_ints
# Purpose: Given a list of objects (strings, ints, or floats), find the 
# average of all the integers on the list by appending them into a new
# list and summing them up and dividing by the total number of ints
# in the list
# Precondition: The inputs don't have to be just integers, they can be
# all sorts of types
# Input Parameter(s)
# objects: a list containing any objects or an empty list
# Return Value(s)
# -- if the input parameter is an empty list, return a list of [0,[]]
# --else return a list with the 0th index position conataining the
# rounded average of all the ints on the list and the 1st index
# containing the inputed list of only ints
#============================================

def average_of_ints(objects):

    integers = []
    for i in objects:
        if type(i) == int:
            integers.append(i)
    
    if integers != []:
        sum = 0
        for i in integers:
            sum += i

        average = round(sum / len(integers))
        return [average, integers]

    else:
        return [0, []]






#==========================================
# Name: max_of_lists
# Purpose: Given a list of more lists, each containg integers, find
# the max value from the entire list. Return the highest value from
# the list that contains the highest value
# Precondition: Hint: The inputed list will only contain more lists,
# each containing integers, there will be no embedded lists inside an
# already embedded list (ex: won't see [1,[1,[3]],4])
# Input Parameter(s)
# mylist: a list containing more lists, or an empty list
# Return Value(s)
# -- if the input parameter is an empty list, return a 0
# -- else return the highest integer found in the list of lists
#============================================

def max_of_lists(mylist):

    if len(mylist) == 0:
        return 0
    
    else:
        n = mylist[0][0]
        for i in mylist:
            
            for j in i:

                if j > n:
                    n = j

        return n






#==========================================
# Name: greater_than
# Purpose: This function takes in a list of different objects and
# an numeric value. The function returns True if all the ints or 
# floats in the list are greater than the inputed number. Otherwise 
# the function returns False.
# Precondition: The first index will be a list of any objecy, 
# and the second index will contain an int or float to compare the 
# two
# Input Parameter(s)
# mylist: a list containing any objects or an empty list
# x: an int or float
# Return Value(s)
# -- if the input parameter is an empty list and a number, return 
# False
# -- if the input parameter contains a list of values that ARE NOT
# all greater than the int / float input, return False
# if the input parameter contains a list of values that ARE all
# greater than the int / float input, return True
#============================================

def greater_than(mylist,x):

    newlist = []
    for i in mylist:
        if type(i) == (int or float):
            newlist.append(i)
    
    greaterThan = True
    for i in newlist:
        if i <= x:
            greaterThan = False
    
    if newlist == []:
        return False
    
    return greaterThan






#==========================================
# Name: selection_sort
# Purpose: Given a list of integers, the function starts from the
# last index position and compares it to the previous ones. The list 
# iterates until it finds the max value in the list, it then swaps
# with i in the final index position. That postition can no longer be
# iterated on as we know it's the max value, so now the list iterates
# over 0 to the new i position, and swapping the new max value with i 
# (if i isn't the max value already). It iterates until the list runs
# to the end and finally terminates with a sorted list.
# Precondition: The list will just contain integers
# Input Parameter(s)
# list: list of integers
# Return Value(s)
# return a sorted list of integers from the min value to the max
#============================================

def selection_sort(list):

    for i in range(len(list) - 1, -1, -1):

        max_index = i
        for j in range(0, i):
            if list[j] > list[max_index]:
                max_index = j
        
        list[max_index] , list[i] = list[i] , list[max_index]
    
    return list


print(max_of_lists([[-3,-4], [-7,-10], [-7,-2]]))