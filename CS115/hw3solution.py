# CS 115 Homework 3     (your file should be named hw3solution.py)
# John Spicer
# 9/24/14
# I pledge my honor that I have abided by the Stevens Honor System


############
# PROBLEM 0 
############

# Implement the function giveChange() here: 
# https://www.cs.hmc.edu/twiki/bin/view/ModularCS1/MakingChange!

def giveChange(amount,coins):
    '''Returns the number of coins needed to make the amount given (from helpChange) and returns the list of coins (from helpChange)'''
    return helpChange(amount,coins, 0, [])

def helpChange(amount,coins, count, L):
    '''Returns the number of coins needed to make the amount given, as well as creating a list of the coins used'''
    if coins == []:
        return [float("inf"),[]]
    
    if amount == 0:
        return [count,L] 
    
    if coins[0] > amount:
        return helpChange(amount, coins[1:], count, L)
        
    lose_it = helpChange(amount, coins[1:], count, L)
    
    use_it = helpChange(amount - coins[0],coins, count + 1, L + [coins[0]])

    return min(use_it,lose_it)

############
# PROBLEM 1
############

# Implement wordsWithScore() which is specified below.
# Hints: Use map.  And use some of the functions you did for
# homework 3 (Scrabble Scoring).  As always, include any helper
# functions in this file, so we can test it.

# Here's the list of letter values and a small dictionary to use.

scrabbleScores = [ ["a", 1], ["b", 3], ["c", 3], ["d", 2], ["e", 1], ["f", 4], ["g", 2], ["h", 4], ["i", 1], ["j", 8], ["k", 5], ["l", 1], ["m", 3], ["n", 1], ["o", 1], ["p", 3], ["q", 10], ["r", 1], ["s", 1], ["t", 1], ["u", 1], ["v", 4], ["w", 4], ["x", 8], ["y", 4], ["z", 10] ]

aDictionary = ["a", "am", "at", "apple", "bat", "bar", "babble", "can", "foo", "spam", "spammy", "zzyzva"]

def letterScore(letter, scoreList):
    """Returns the score of a letter"""
    if scoreList == []:
        return 0
    elif letter == scoreList[0][0]:
        return scoreList[0][1]
    return letterScore(letter, scoreList[1:])


def wordScore(S,scoreList):
    """Returns the score of a word based on a list of scores"""
    if S == "":
        return 0
    return letterScore(S[0],scoreList) + wordScore(S[1:],scoreList)



def wordsWithScore(dict, scores):
    """List of words in dict, with their Scrabble score.

    Assume dict is a list of words and scores is a list of [letter,number] pairs.
    return the dictionary annotated so each word is paired with its value.
    For example, wordsWithScore(scrabbleScores, aDictionary) should return
    [["a", 1], ["am", 4], ["at", 2] ...etc... ]
    """
    
    if dict == []:
        return []
    

    return  [[dict[0],wordScore(dict[0],scores)]] + wordsWithScore(dict[1:],scores)

print "Testing wordsWithScore"
print wordsWithScore(aDictionary,scrabbleScores)

############
# PROBLEM 2
############

# For the sake of an exercise, we will implement a function
# that does a kind of slice.  You must use recursion for this
# one.  Your code is allowed to refer to list index L[0] and
# also use slice notation L[1:] but no other slices.

def take(n, L):
    '''return the list L[0:n]'''
    if L == []:
        return []
    if n == 0:
        return []
    return [L[0]] + take(n-1,L[1:])  

# Code to use for testing
def testTake(n,L):
    '''computes L[0:n] using the function above and checks the answer'''
    if take(n,L)==L[0:n]:
        print "test ok"
    else: print "my test failed"


testTake(0, ["not", "it", "works", "!"])
testTake(2, ["not", "it", "works", "!"])
testTake(4, ["not", "it", "works", "!"])


############
# PROBLEM 3
############

# Similar to problem 2, will implement another function
# that does a kind of slice.  You must use recursion for this
# one.  Your code is allowed to refer to list index L[0] and
# also use slice notation L[1:] but no other slices.
    
def drop(n, L):
    '''return the list L[n:]'''
    if L == []:
        return []
    if n == 0:
        return L
    
    return drop(n-1, L[1:])

def testDrop(n,L):
    '''computes L[n:] using the function above and checks the answer'''
    if drop(n,L)==L[n:]:
        print "test ok"
    else: print "my test failed"

testDrop(0, ["I", "am", "nearly", "done"])
testDrop(1, ["I", "am", "nearly", "done"])
testDrop(3, ["I", "am", "nearly", "done"])




