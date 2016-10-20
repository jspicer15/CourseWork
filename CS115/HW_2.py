scrabbleScores = [ ["a", 1], ["b", 3], ["c", 3], ["d", 2], ["e", 1], ["f", 4], ["g", 2], ["h", 4], ["i", 1], ["j", 8], ["k", 5], ["l", 1], ["m", 3], ["n", 1], ["o", 1], ["p", 3], ["q", 10], ["r", 1], ["s", 1], ["t", 1], ["u", 1], ["v", 4], ["w", 4], ["x", 8], ["y", 4], ["z", 10] ]
Dictionary = ["a", "am", "at", "apple", "bat", "bar", "babble", "can", "foo", "spam", "spammy", "zzyzva"]

def letterScore(letter, scoreList):
    '''Returns the score of a particular letter based on a list of scores'''
    if letter == scoreList[0][0]:
        return scoreList[0][1]
    if scoreList == []:
        return 'error in letter or scoreList'
    return letterScore(letter, scoreList[1:])

def wordScore(S,scoreList):
    '''Returns the score of a particular word based on a list of scores'''
    if S == "":
        return 0
    return letterScore(S[0],scoreList) + wordScore(S[1:],scoreList)



def explode(S):
    """Returns a list of the characters in string S"""
    if S == "":
        return []
    return   [S[0]] + explode(S[1:])

def removeAll(e,L):
    '''Returns list L with all instances of 'e' removed'''
    if L == []:
        return []
    if e == L[0]:
        return removeAll(e,L[1:])
    return  removeAll(e,L[1:]) + [L[0]]

def checkWord(Rack,dic):
    '''Checks the first letter of word 'w' and returns a list with all instances
including letter w[0] in the dictionary'''
    if dic == []:
        return [] 
    if Rack == []:
        return []
    if dic[0] in Rack:
        return [dic[0]] + checkWord(Rack[0],dic[1:])
    return checkWord(Rack[0],dic[1:]) 



def checkWords(w,dic):
    if dic == []:
        return [] 
    if w == []:
        return []
    #if 
def checkList(Rack):
    if Rack == []:
        return []
    return checkWord(Rack[0],Dictionary) + checkList(Rack[1:]) 
            


#def ScoreList(Rack):
