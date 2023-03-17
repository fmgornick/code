def cntWordsOccur(sentence):
    sentences = sentence.split()
    new_list = []
    new_new_list = []
    for i in sentences:
        if i not in new_list:
            new_list.append(i)
    for j in new_list:
        n = sentences.count(j)
        new_new_list.append([j,n])
    return new_new_list

print(cntWordsOccur(' i i you teaath ald got got te feor'))
