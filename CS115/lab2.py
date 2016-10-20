def dot(L,K):
    """retuns the dot product of lists L and K"""
    if L == K == []:
        return 0.0
    if L == K:
        return dot(L[1:],K[1:]) + L[0] * K[0]
    return "L and K are different lengths"

def explode(S):
    """Returns a list of the characters in string S"""
    if S == "":
        return []
    return   [S[0]] + explode(S[1:])

def ind(e,L):
    """Returns the position at which e is found first in sequence L"""
    if e == L[0]:
        return 0
    if L == [] or L == "":
        return 0
    else:
        return ind(e,L[1:]) + 1

def removeAll(e,L):
    if L == []:
        return []
    if e == L[0]:
        return removeAll(e,L[1:])
    return  removeAll(e,L[1:]) + [L[0]]

def even(X):
    if X % 2 == 0: return True
    else: return False

def myFilter(f,L):
    if L == []:
        return L
    if f(L[0]) == True:
        return [L[0]] + myFilter(f,L[1:])
    return myFilter(f,L[1:])

def deepReverse(L):
    if L == []:
        return L
    if type(L[0]) == list:
        return deepReverse(L[1:]) + [deepReverse(L[0])]
    return deepReverse(L[1:])+[L[0]]



        
