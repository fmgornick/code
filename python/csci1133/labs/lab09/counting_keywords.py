def keywordCount(filename):
    keyword_dict = {
    'False': 0,
    'None': 0,
    'True': 0,
    'and': 0,
    'as': 0,
    'assert': 0,
    'async': 0,
    'await': 0,
    'break': 0,
    'class': 0,
    'continue': 0,
    'def': 0,
    'del': 0,
    'elif': 0,
    'else': 0,
    'except': 0,
    'finally': 0,
    'for': 0,
    'from': 0,
    'global': 0,
    'if': 0,
    'import': 0,
    'in': 0,
    'is': 0,
    'lambda': 0,
    'nonlocal': 0,
    'not': 0,
    'or': 0,
    'pass': 0,
    'raise': 0,
    'return': 0,
    'try': 0,
    'while': 0,
    'with': 0,
    'yield': 0}
    file_pointer = open(filename, 'r')
    line = file_pointer.readlines()
    for i in line:
        words = i.split()
        for i in words:
            if i in keyword_dict:
                keyword_dict[i] += 1
    return keyword_dict

