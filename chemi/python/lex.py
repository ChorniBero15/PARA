class Lexicon:
    def __init__(self, path):
        self.words = []
        f = open(path, "r")
        for word in f:
            self.words.append(word[:-2])
    
    def allWords(self):
        for word in self.words:
            print(word)
        
    def containsWord(self, word):
        return word in self.words
    
    def wordsContaining(self, sub_word):
        return [word for word in self.words if sub_word in word]
    
