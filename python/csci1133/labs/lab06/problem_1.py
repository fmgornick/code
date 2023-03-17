def cntWordOccur(sentences, word):
    sent = sentences.split()
    n = 0
    for i in sent:
        if i == word:
            n += 1
    return n



