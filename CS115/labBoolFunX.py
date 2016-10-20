# labBoolFun 16 oct 2013

# First implement the two functions described in the following URL
# https://www.cs.hmc.edu/twiki/bin/view/ModularCS1/TwosComplement
def numToBinary(N):
    '''converts a decimal number to a binary number'''
    if N == 0:
        return ''
    return numToBinary(N/2) + str(N % 2)

def binaryToNum(S):
    '''converts a binary number to a decimal number'''
    def helpBin(S,Y):        
        if S == '':
            return 0
        elif int(S[-1]) == 0:
             return helpBin(S[0:-1],Y+1)
        return helpBin(S[0:-1],Y+1) + 2 ** Y
    return helpBin(S,0)

def numBits(N,k):
    '''Uses the numToBinary function to create binary strings that are k number
       of bits'''
    if len(numToBinary(N)) < k:
        return '0' * (k - len(numToBinary(N))) + numToBinary(N)
    else:
        return numToBinary(N)

def TcToNum(S):
    '''Converts a number in Two's compliment to decimal'''
    if int(S[0]) == 0:
        return int(binaryToNum(S))
    else:
        return int(binaryToNum(S)) - 256

def NumToTc(S):
    '''converts a decimal number to the Two's compliment of that number'''
    if S > 127:
        return 'Error'
    elif S < -128:
        return 'Error'
    elif S >= 0:
        return numBits(S,8)
    else:
        return numBits(S + 256,8)
# Now do the folllwing exercises

# Step 1. 

# Implement the following.  

def combs(n):
    '''Assume n >= 1.  Return a list of all lists of n bits, in binary
    numerical order.  For example combs(2) is [[0,0],[0,1],[1,0],[1,1]].
    Hints:  Think recursively, sort of like use-it-or-lose-it.
    Use map and lambda and also recursive call combs(n-1).      
    '''
    if n == 1:
        return [[0],[1]]
    else:
        nxt = combs(n-1)
        return map(lambda x: [0] + x , nxt) + map(lambda x: [1] + x, nxt)


# Step 2.

# The following function is intended to be applied to booleans.
# For example, func0(1,0,1) returns 1 (which may display as True).

def func0(x,y,z): return x and (y or z)

# We would like to try this function on all possible inputs.
# Try this:  map(func0, combs(3))
# Think about why it doesn't work.

# Try this, which works:  
#      map(lambda args: func0(*args), combs(3))
# The syntax *args says to pass the elements of args to func0 as three
# separate arguments, e.g., func0(*[1,0,1]) is func0(1,0,1).

# Implement the following.

def func0table():
    '''Return the list [([0,0,0], 0), ([0,0,1], 0), ... , ([1,1,1], 1)]
        which represents the truth table for func0.  In other words
        list all the tuples ([x,y,z], func0(x,y,z)).
        Hint: Use map, similarly to 'Try this' above.
    '''
    def helps(x,y):
        if x == []:
            return []
        if y == []:
            return []
        return [[x[0],y[0]]] + helps(x[1:],y[1:])
    func = map(lambda x: func0(*x), combs(3))
    return helps(combs(3),func)   


# Here is a function that displays the result as a table.

def showTable(lst):
    '''Assume lst is in the format returned by func0table(). Print it.
    '''
    if lst == []: return None
    else:
        print lst[0][0], lst[0][1]
        showTable(lst[1:])

# Step 3.

# Based on the truth table for func0, we defined the following alternate
# implementation for the same function. (It's called the 'minterm principle.')
# Have a look:

def func0alt(x,y,z):
    return ( (x and not y and z)
             or (x and y and not z)
             or (x and y and z) )

# Implement this test that compares func0 with func0alt.


def func0alttable():
    def helpalt(x,y):
        if x == []:
            return []
        if y == []:
            return []
        return [[x[0],y[0]]] + helpalt(x[1:],y[1:])
    func = map(lambda x: func0alt(*x),combs(3))
    return helpalt(combs(3),func)
    
def func0test():
    '''Applies func0 and func0alt to all possible inputs.  Returns True
        if they agree in every case, otherwise False.  
        Hint: one way uses map and then reduce.'''
    def helps(x,y):
         if x == []:
             return True
         elif x[0][1] == y[0][1]:
              return helps(x[1:],y[1:])
         else:
           return False
       
    return helps(func0table(),func0alttable())
    

# Step 4.

# You will play the same game with this function:
def func1(x,y): return x or (y and x)

# Implement these functions:

def func1table():
    '''Return a table of values of func1, 
        so they can be displayed using showTable.
    '''
    def helps(x,y):
        if x == []:
            return []
        else:
            return [[x[0],y[0]]] + helps(x[1:],y[1:])
    func = map(lambda x: func1(*x), combs(2))
    return helps(combs(2),func)

def func1alt(x,y):
    '''Return func1(x,y), computed based on the minterm principle.
    '''
    return ( (x and not (x and y))
             or (x or y )
             )

def func1alttable():
    def helpalt1(x,y):
        if x == []:
            return []
        if y == []:
            return []
        return [[x[0],y[0]]] + helpalt1(x[1:],y[1:])
    func = map(lambda x: func1alt(*x),combs(2))
    return helpalt1(combs(2),func)

def func1test():
    '''Apply func1 and func1alt to all possible inputs.  Return True or
        False depending on whether they agree in every case.
    '''
    def helps(x,y):
     if x == []:
         return True
     elif x[0][1] == y[0][1]:
         return helps(x[1:],y[1:])
     else:
         return False
       

    return helps(func1table(),func1alttable())
    

