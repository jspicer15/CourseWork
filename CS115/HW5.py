# CS 115 HW 5
# John Spicer
# 10/5/14
# I pledge my honor that I have abided by the Stevens Honor System

# Write your solution to the svTree function in this file as well
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

def fastFib(n):
    """Returns the nth fibonacci number using the memoization technique
    shown in class and lab. Assume that the 1st finacci number is 1 so fastFib(1) = 1,
    fastFIb(2) = 1 and fastFib(3) = 2"""
    memo = {0:0, 1:1}
    if not n in memo:
        memo[n] = fastFib(n-1) + fastFib(n-2)
    return memo[n]

print fastFib(3)
print fastFib(9)
print fastFib(24)
print fastFib(40)
