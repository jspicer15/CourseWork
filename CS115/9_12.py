def my_sum(lst):
    if len.lst == 1:
        return lst[0]
    return lst[0] + my_sum(lst[1:]) 

def square_all(lst):
    if lst == []:
        return []
    return [lst[0] * lst[0]] + square_all(lst[1:])

def power(x,y):
    if y == 0:
        return 1
    return x * power(x,y-1) 

def my_reduce(f,lst):
    if lst[1:] == []:
        return lst[0]
    return f(lst[0], my_reduce(lst(f,lst[1:])))

def my_map(f,lst):
    if lst == []:
        return
    return [f(lst[0])] + my_map(f,lst[1:])
