import turtle

def tree(length,n):
    """ paints a branch of a tree with 2 smaller branches, like an Y"""
    if length < (length/n):
           return       # escape the function
    turtle.forward(length)        # paint the thik branch of the tree
    turtle.left(45)          # rotate left for smaller "fork" branch
    tree(length * 0.5,length/n)      # create a smaller branch with 1/2 the lenght of the parent branch
    turtle.right(90)         # rotoate right for smaller "fork" branch
    tree(length * 0.5,length/n)      # create second smaller branch
    turtle.left(45)          # rotate back to original heading
    turtle.backward(length)       # move back to original position
    return              # leave the function, continue with calling program
