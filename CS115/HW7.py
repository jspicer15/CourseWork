def numToBaseB(N,B):
    '''converts a decimal number to a number in base B'''
    if N == 0:
        return ''
    return numToBaseB(N/B,B) + str(N % B)

def baseBToNum(S,B):
    '''converts a number in base B to a decimal number'''
    def helpB(S,Y):        
        if S == '':
            return 0
        elif int(S[-1]) == 0:
             return helpB(S[0:-1],Y+1)
        return helpB(S[0:-1],Y+1) + (B ** Y * int(S[-1]))
    return helpB(S,0)

def baseToBase(B1,B2,SinB1):
    '''converts a number SinB1 in base B1 to base B2'''
    return numToBaseB(baseBToNum(SinB1,B1),B2)

def add(S,T):
    '''adds two binary numbers using decimal conversion'''
    return numToBaseB((baseBToNum(S,2) + baseBToNum(T,2)),2)

def addB(S1,S2):
    '''adds two binary numbers using 'carry' bits '''
    def sameLength(S1,S2):
        '''makes two binary numbers the same number of bits'''
        if len(S1) == len(S2):
            return S1,S2
        elif len(S1)< len(S2):
            return '0' * (len(S2)-len(S1)) + S1,S2
        else:
            return S1, '0' * (len(S1)-len(S2)) + S2
    def carry1(S1,S2,X):
        '''carries the bits in the addition of the two binary strings'''
        if S1 == '':
            if X == 0:
                return ''
            else:
                return '1'
        elif int(S1[-1]) + int(S2[-1]) + X == 0:
            return carry1(S1[:-1],S2[:-1],0) + '0'
        
        elif int(S1[-1]) + int(S2[-1]) + X == 1:
            return carry1(S1[:-1],S2[:-1],0) + '1'

        elif int(S1[-1]) + int(S2[-1]) + X == 2:
            return carry1(S1[:-1],S2[:-1],1) + '0'

        elif int(S1[-1]) + int(S2[-1]) + X == 3:
            return carry1(S1[:-1],S2[:-1],) + '1'
        
    s1 = sameLength(S1,S2)[0]
    s2 = sameLength(S1,S2)[1]
    return carry1(s1,s2,0)

        
