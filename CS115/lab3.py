def change(amount, coins):

    
    if coins == []:
        return float("inf")
    
    if amount == 0:
        return 0
    
    if coins[0] > amount:
        return change(amount, coins[1:])
        
    lose_it = change(amount, coins[1:])
    
    use_it = change(amount - coins[0],coins) + 1

    return min(use_it,lose_it)
    

def giveChange(amount,coins):
    return helpChange(amount,coins, 0, [])

def helpChange(amount,coins, count, L):
    if coins == []:
        return [float("inf"),[]]
    
    if amount == 0:
        return [count,L] 
    
    if coins[0] > amount:
        return helpChange(amount, coins[1:], count, L)
        
    lose_it = helpChange(amount, coins[1:], count, L)
    
    use_it = helpChange(amount - coins[0],coins, count + 1, L + [coins[0]])

    return min(use_it,lose_it)

    
