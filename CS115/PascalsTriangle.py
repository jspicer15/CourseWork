#I pledge my honor that I have abided by the Stevens Honor System
# John Spicer

def add(lst):
    """Returns a list of the sum of adjecent integers in the given lst"""
    if len(lst) == 1:
        return []
    return [lst[0]+lst[1]]+ add(lst[1:])

def pascal(row):
    """Returns the list of the elements of the row of Pascal's Triangle given"""
    if row == 0:
        return [1]
    if row == 1:
        return [1,1]
    prev_row = pascal(row-1)
    return [1] + add(prev_row) + [1]
