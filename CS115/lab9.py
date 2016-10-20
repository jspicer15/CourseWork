from cs5png import *




def mult(c,n):
    result = 0
    for x in range(n):
        result = result+c
    print result

def update(c,n):
    z = 0
    for x in range(n):
        z = z **2 +c
    return z

def inMSet(c,n):
    z = 0
    for x in range(n):
        if abs(z) > 2:
            return False
        z = z **2 +c

    return True
