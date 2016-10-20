import turtle

def svTree(length,n):
    """ paints a tree with branches of decreasing length, the trunk starting
        at the length of the first number provided with n number of sub branches"""

    if n ==0:
        return
    if length < (length/n):
        return
    turtle.pencolor("brown")
    turtle.forward(length)      
    turtle.left(45)
    svTree(length * 0.5,n-1)
    turtle.right(90)
    svTree(length * 0.5,n-1)
    turtle.left(45)
    turtle.backward(length)    
