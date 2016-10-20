def isOdd(n):
    """returns true for odd numbers and false for even number"""
    return n % 2 != 0
#For odd numbers the least-significant bit will be a 1 to signify 2**0 which is
# 1 in base 10. For even number this bit will be 0

#The value of the original number will decrease by either 1 or 0

# if N is even
# if N is odd then it will be the same binary number as N - 1 but instead the
# least-significant number will be a 1 instead of a 0


def numToBinary(N):
    if N == 0:
        return ''
    return numToBinary(N/2) + str(N % 2) 

    
def binaryToNum(S):
    def helpBin(S,Y):        
        if S == '':
            return 0
        elif int(S[-1]) == 0:
             return helpBin(S[0:-1],Y+1)
        return helpBin(S[0:-1],Y+1) + 2 ** Y
    return helpBin(S,0)

def increment(S):
    if len(numToBinary(binaryToNum(S) + 1)) < 8:
        return '0' * (8 - len(numToBinary(binaryToNum(S) + 1))) + numToBinary(binaryToNum(S) + 1)
    elif len(numToBinary(binaryToNum(S) + 1)) > 8:
        return numToBinary(binaryToNum(S) + 1)[1:]
    else:
        return numToBinary(binaryToNum(S) + 1)

def count(S,n):
    if n == 0:
        return 
    print S
    return count(increment(S),n-1)

def numToTernary(N):
    if N == 0:
        return ''
    return numToTernary(N/3) + str(N % 3)

def ternaryToNum(S):
    def helpTern(S,Y):
        if S == '':
            return 0
        elif int(S[-1]) == 0:
            return helpTern(S[0:-1],Y+1)
        return helpTern(S[0:-1],Y+1) + (int(S[-1]) * 3 ** Y)
    return helpTern(S,0)
