def knapsack(capacity, itemList):
    if itemList == []:
        return [0,[]]
    
    if capacity == 0:
        return [0,[]]
    
    if capacity < itemList[0][0]:
        return knapsack(capacity,itemList[1:])
    
    lose_it = knapsack(capacity,itemList[1:])
    use_it = knapsack(capacity-itemList[0][0],itemList[1:])
    use_it = [use_it[0] + itemList[0][1], use_it[1]+[itemList[0]]]

    
    return max(use_it,lose_it)

def fib(n):
    if n == 1:
        return [1]
    if n == 2:
        return [1,1]
    else:
        x = fib(n-1)
        return x + [x[-1] + x[-2]]
