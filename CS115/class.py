lst = [2,4,3,7]

def increment_all(lst,k):
    def increment_one(addend):
        return k + addend
    return map(increment_one,lst)
