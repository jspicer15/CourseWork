Penguin = "00011000"+"00111100"*3 + "01111110"+"11111111"+"00111100"+"00100100"
Smile = "0"*8 + "01100110"*2 + "0"*8 + "00001000" + "01000010" + "01111110" + "0"*8
Five = "1"*9 + "0"*7 + "10000000"*2 + "1"*7 + "0" + "00000001"*2 + "1"*7 + "0" 

# John Spicer, Laramie Regalado
# I pledge my honor that I have abided by the Stevens Honor System


def numToBinary(N):
    '''converts a decimal number to a binary number'''
    if N == 0:
        return ''
    return numToBinary(N/2) + str(N % 2)

def numBits(N,k):
    '''Uses the numToBinary function to create binary strings that are k number
       of bits'''
    if len(numToBinary(N)) < k:
        return '0' * (k - len(numToBinary(N))) + numToBinary(N)
    else:
        return numToBinary(N)

def binaryToNum(S):
    '''converts a binary number to a decimal number'''
    def helpBin(S,Y):        
        if S == '':
            return 0
        elif int(S[-1]) == 0:
             return helpBin(S[0:-1],Y+1)
        return helpBin(S[0:-1],Y+1) + 2 ** Y
    return helpBin(S,0)

def compress(S):
    '''Compresses a binary string using run-length encoding with fixed number
        of bits k for each term'''
    k = 5
    
    def helpCompressZero(S):
        '''returns the number of zeros in a row'''
        if S == '':
            return 0
        elif int(S[0]) == 0:
            return 1 + helpCompressZero(S[1:])
        else:
            return 0

    def helpCompressOne(S):
        '''returns the number of ones in a row'''
        if S == '':
            return 0
        elif int(S[0]) == 1:
            return 1 + helpCompressOne(S[1:])
        else:
            return 0
        
    if S == '':
        return ''
    elif int(S[0]) == 0:
        return '0' + numBits(helpCompressZero(S),k) + compress(S[helpCompressZero(S):])
    elif int(S[0]) == 1:
        return '1' + numBits(helpCompressOne(S),k) + compress(S[helpCompressOne(S):])

  # The maximum number of bits that the compress algorithm above could use
  # would be 384, because there would be a maximum of 64 individual strings if
  # the 64-bit string/image was 01 or 10 * 64 and 5 bits would be used to
  # represent the number of ones or zeros, there would be 6 bits for each
  # single bit of the 64 bit string/image 

def uncompress(S):
    '''return the binary number represeted by the compressed string'''
    k = 5
    if S == '':
        return ''
    elif int(S[0]) == 0:
        return '0' * binaryToNum(S[1:k+1]) + uncompress(S[(k+1):])
    elif int(S[0]) == 1:
        return ('1' * binaryToNum(S[1:k+1])) + uncompress(S[(k+1):])

def compressionTest():
    '''prints the uncompressed and compressed strings for the images provided,
    as well as the compression ratios in the form compressed / uncompressed'''
    print "Penguin:" + Penguin
    print "compressed Penguin:" + compress(Penguin)
    print "compression ratio: " + str(len(compress(Penguin)) * 1.0 / len(Penguin)) 
    print
    print "Smile:" + Smile
    print "compressed Smile:" + compress(Smile)
    print "compression ratio: " + str(len(compress(Smile)) *1.0 / len(Smile))
    print
    print "Five:" + Five
    print "compressed Five:" + compress(Five)
    print "compression ratio: " + str(len(compress(Five)) * 1.0 / len(Five))

# the compression tests for the images show that the run length encoding
# compression algorithm creates compressed strings that are longer than the
# initial strings, as indicated by the compression ratios being > 1


# Lai's algorithm cannot exist because with certain groupings of bits,
# you will still have at least 64 bits and for some combinations over 64. For example if there was a string of
# 01 * 32 the compressed algorithm using run-length encoding would also be
# 384 bits. An algorithm like this could not be acheived because the algorithm would
# be using multiple bits, to compress even a single bit in the uncompressed string.
# For example if there was a 1 followed by any number of 0's, the compression
# algorithm would need to represent that 1 with more than one bit.





# By John Spicer
