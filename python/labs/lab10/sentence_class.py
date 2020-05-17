class Sentence:

    def __init__(self, mystring):
        self.mystring = mystring

    def __str__(self):
        return self.mystring
    
    def getSentence(self):
        return self.mystring
    
    def getWords(self):
        list_words = self.mystring.split(' ')
        return list_words
    
    def getLength(self):
        return len(self.mystring)
    
    def getNumWords(self):
        return len(self.getWords())



class SentenceV1:

    def __init__(self, mystring):
        self.mystring = mystring.split(' ')
    
    def __str__(self):
        return self.mystring
    
    def getWords(self):
        return self.mystring
    
    def getLength(self):
        sum = 0
        for i in self.mystring:
            sum += len(i) 
        return sum

    def getNumWords(self):
        return len(self.mystring)



stri = 'the quick brown fox jumped over the lazy dog'
sent = SentenceV1(stri)
print(sent.getLength())