def reverseString(word):
    if len(word) == 0:
        return ''
    else:
        return word[-1] + reverseString(word[:-1])