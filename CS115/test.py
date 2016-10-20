import math

def add(x,y):
    return x+y

def inverse(n):
    return 1.0/n

def e(n):
   list1 = map(math.factorial, range(0, n+1)) 
   list2 = map(inverse, list1)
   return reduce(add, list2)
  
    
def error(n):
    return abs(math.e-e(n))

