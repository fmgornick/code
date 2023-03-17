words = []
tf = True
while(tf):
    word = input('Insert word: ')
    if word = '':
        tf = False
    else:
        for i in range(1, word):
            if word[0] == word[i]:
                if word not in words:
                    words.append(word)

print(words)
