# CSCI 1133, Fletcher Gornick, gorni025
# lab Section 002, HW 6

#==========================================
# Name: sameKeys

# Purpose: find similar key values in two separate dictionaries, and add them to a
# new dictionary with the shared key.  Assign a list of the values from the other
# two keys to the new dictionary key

# Precondition: both dictionaries can be empty, there can be any type of object in
# the inputs, values are sorted by input, and we're creating a new dictionary

# Input Parameter(s): Two dictionaries with anything in them

# Return Value(s): A new dictionary containing keys that are in both input dicts,
# and lists of values assigned to those keys
#==========================================

def sameKeys(dict1, dict2):
    dict3 = {}
    if len(dict1) >= len(dict2):
        for key in dict1:
            if key in dict2:
                dict3[key] = [dict1[key], dict2[key]]
    else:
        for key in dict2:
            if key in dict1:
                dict3[key] = [dict1[key], dict2[key]]
    return dict3



#==========================================
# Name: averageHours

# Purpose: to take in a dictionary containing employees and hours worked per week
# and returning each worker's average hourly work week

# Precondition: return an empty dictionary if an empty one is passed in, each key
# value will be a list of integers or an empty list (if empty, return 0 for avg),
# and using sorting function given to create a sorted list

# Input Parameter(s): a dictionary with keys representing employees and values
# representing their hours worked per week

# Return Value(s): a new dictionary with keys representing employees and values
# representing their average of hours worked per week
#==========================================

def averageHours(dict):
    if dict == {}:
        return {}
    newdict = {}
    for key in dict:
        if dict[key] == []:
            newdict[key] = 0
        else:
            newdict[key] = round(sum(dict[key]) / len(dict[key]))
    newlist = []
    for i in sorted(newdict):
        newlist.append(i)
        newlist.append(newdict[i])
    return newlist



#==========================================
# Name: allKeys

# Purpose: you have a dictionary with string keys and list values, you're also
# given a list.  If there's an integer in one of the key's value / lists that's
# also in the second inputed list, that key will be appended to a new list

# Precondition: The keys are only assigned lists (empty or with integers), the
# passed in list will only contain integers, don't change the dictionary, the list
# should be sorted, keys are always strings, any built ins

# Input Parameter(s): (1) A dictionary with strings as the keys, and a list of ints
# for the key's values, and (2) a list of integers

# Return Value(s): a sorted list of keys from the input dictionary if they share
# an integer in their value list with the second input list
#==========================================

def allKeys(diction, element):
    if diction == {} or element == []:
        return []
    newlist = []
    for key in diction:
        for value in diction[key]:
            if value in element:
                if key not in newlist:
                    newlist.append(key)
    return sorted(newlist)
    