def mult(x,y):
    """Returns the product of x y"""
    return x * y

def add(x,y):
    """Returns the sum of x y"""
    return x + y

def factorial(n):
    """Finds the factorial of n"""
    if n != 0:
        return reduce(mult, range(1,n+1))
    else:
        return 1

def mean(L):
    """Finds the mean of the list 1,L"""
    L = range(1,L+1)
    return reduce(add,L)* 1.0 / len(L)

def divides(n):
    """Returns true if n is evenly divisible by k,
    and false if there is a remainder"""
    def div(k):
        return n % k == 0
    return div

def prime(n):
    """Checks if n is a prime or composite number"""
    if reduce(add,map(divides(n),range(2,n))) == 0:
        return "Prime"
    return "Composite"

    

#I pledge my honor that I have abided by the Stevens Honor System-John Spicer
