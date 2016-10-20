'''
Demonstration of encapsulation and mutability.

For more about 'private variables', search for them at
https://docs.python.org/2/tutorial/classes.html

'''
class Student:
    '''A student has a name (immutable), favorite color (mutable),
        and some grades.'''
    
    def __init__(self,nameString,colorString):

        # Note: names of the form __stuff (without trailing underscore)
        # get automatically 'mangled' to the form _Student__stuff throughout the class.
        self.__name = nameString
        self.__faveColor = colorString
        self.__grades = []

    def getName(self): return self.__name

    def getFaveColor(self): return self.__faveColor

    def setFaveColor(self,colorString): self.__faveColor = colorString

    def __repr__(self):
        
        return "Student " + self.__name + ", who likes " + self.__faveColor

    def addGrade(self,score):
        '''Add score to list of grades (assume score is number in range 0..100).'''
        self.__grades += [score]

    def getGrades(self): return self.__grades

    
alice = Student("Alice", "red")
bob = Student("Bob", "blue")

bob.setFaveColor( alice.getFaveColor() )

print "Bob now likes " + bob.getFaveColor()

alice.addGrade(100)
alice.addGrade(80)
bob.__grades = [0,0]  

print "Alice's grades " + str(alice.getGrades())
print "Bob's grades " + str(bob.getGrades())

agrad = alice.getGrades()
print "Alice's average is " + str(sum(agrad)/len(agrad))



alice.__grades = [100,100]
print "Alice's changed grades?" + str(alice.getGrades())

# agrad[1] = 100
# print "Alice's changed grades!" + str(alice.getGrades())


                 
    
 
