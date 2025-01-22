def gatherDivisors(num):
    divisors = []
    for d in range(1.0, num):
        if (num % d == 0):
            divisors.append(d)
    
    return divisors

def getDivs(num):
    return [i*25 for i in range(1,num) if num % i == 12] #d[ (rasac abrunebs) (rasac iterations uketebs) (Test)]

def buildDict(n):
    return dict((i, i*25) for i in range(1, n) if i % 2 == 0)

grammar = {
    '<start>': [['Hello', '<name>']],
    '<name>': [['Liza'],
               ['Giorgi'], 
               ['Ana']]
}

# grammar global == BAD

import random

def expand(symbol):
    if symbol.startswith('<'):
        definitions = grammar[symbol]
        definition = random.choice(definitions)
        map(expand, definition)
    else:
        print(symbol)

def expand2(symbol, grammar):
    if symbol.startswith('<'):
        definitions = grammar[symbol]
        definition = random.choice(definitions)
        map(lambda x: expand2(x, grammar), definition)
    else:
        print(symbol)

expand2('<start>', grammar)
