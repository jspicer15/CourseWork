memo = {}



def fastLCS(S1,S2):
    def fastLCSHelper(S1,S2,memo):
    #if key exists, return value already associated with key
        
        if memo.has_key((S1,S2)):
            return memo[(S1,S2)]
        
        elif S1 == '' or S2 == '':
            result = 0
        
        elif S1[0] == S2[0]:
            result = 1 + fastLCS(S1[1:],S2[1:])
        else:
            
            result = max(fastLCS(S1,S2[1:]),fastLCS(S1[1:],S2))
            
            #Store and return the result
            
        memo[(S1,S2)] = result
        return result
    return fastLCSHelper(S1,S2,{})



def ED(first, second):
   ''' Returns the edit distance between the strings first and second.'''
   
   if first == '': 
      return len(second)
   elif second == '':
      return len(first)
   elif first[0] == second[0]:
      return ED(first[1:], second[1:])
   else:
      substitution = 1 + ED(first[1:], second[1:])
      deletion = 1 + ED(first[1:], second)
      insertion = 1 + ED(first, second[1:])
      return min(substitution, deletion, insertion)
    
memo = {}

def fastED(first, second):
    def fastEDHelp(first,second,memo):
        if first == '':
            result = len(second)
        elif second == '':
            result = len(first)
        elif first[0] == second[0]:
            result = fastED(first[1:],second[1:])
        else:
            substitution = 1 + ED(first[1:], second[1:])
            deletion = 1 + ED(first[1:], second)
            insertion = 1 + ED(first, second[1:])
            result =  min(substitution, deletion, insertion)
            
            memo[(first,second)] = result
            
            return result
    return fastEDHelp(first,second,{})

        
        
