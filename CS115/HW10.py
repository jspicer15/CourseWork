# A very simple music recommender system.
#John Spicer
#I pledge my honor that I have abided by the Stevens Honor System

PREF_FILE = "musicrecPlus.txt"



def createMenu(userMap):
    '''creates a text menu for the user to choose options from'''
    print '\n' + """Enter a letter to choose an option:
    e - enter preferences
    r - get recommendations
    p - show most popular artists
    h - how popular is the most popular
    m - which user has the most likes
    q - save and quit
    """
    option = raw_input("")
    if option != 'q':
        
        if option == 'e':
            user = raw_input("Enter a user name:")
            prefs = getPreferences(user,userMap)
            saveUserPreferences(user, prefs, userMap, PREF_FILE)

        elif option == 'r':
            user = raw_input("Enter a user name:")
            prefs = getPrefs(user,userMap)
            recs = getRecommendations(user,prefs,userMap)
            print '\n'
            print user + ',' + "based on the users I currently" 
            print "know about, I believe you might like:"
            for artist in recs:
                print(artist)
            print '\n'
            print("I hope you enjoy them! I will save your")
            print("preferred artists and have new")
            print("recommendations for you in the future")
           
        elif option == 'p':
            mostPopular(artistLikes(userMap))
            
        elif option == 'h':
            mostLikes(artistLikes(userMap))
            
        elif option == 'm':
            maxLikes(userMap)
            
        else:
            print "Enter one of the options above " + '\n' 
        createMenu(userMap)        
    else:
        print "Goodbye!"
        return        

def artistLikes(userMap):
    '''returns a dictionary containing the artists with the number of likes they have between all the users'''
    votes = {}
    for user in userMap:
        for artist in userMap[user]:
            artists=artist.strip()
            if artists in votes:
                votes[artists] = votes[artists] + 1
            else:
                votes[artists] = 1
    return votes

def mostPopular(likes):
    '''prints the most popular artist'''
    mostPop = []
    for artist in likes:
        if mostPop == []:
            mostPop = [artist]

        else:
            
            if likes[artist] > likes[mostPop[0]]:
                mostPop = [artist]

            elif likes[artist] == likes[mostPop[0]]:
                mostPop = mostPop + [artist]
                
            
    print "The most popular artist(s) : " + str(mostPop) + '\n'

def mostLikes(likes):
    '''prints the number of likes that the most popular artist has'''
    most = 0
    for artist in likes:
        if likes[artist] > most:
            most = likes[artist]
    print "the number of likes of the most liked artist(s) is %s likes" % most + '\n'
        

def maxLikes(userMap):
    '''prints the user(s) with the most likes and their likes, unless their name contains a $, which is used to
        opt out of this '''
    mostLikes = 0
    theUser = []
    for user in userMap:
        if '$' in user:
            pass
        elif len(userMap[user]) > mostLikes :
            mostLikes = len(userMap[user])
            theUser = [user]
        elif len(userMap[user]) == mostLikes:
            mostLikes = len(userMap[user])
            theUser = theUser + [user]
    print 'The user(s) with the most likes: '  + str(theUser) + '\n'
    print 'The liked artists are as follows: ' 
    for users in theUser:
        print users + ':' + str(getPrefs(users,userMap))
    
    
def loadUsers(fileName):
    ''' Reads in a file of stored users' preferences
        stored in the file 'fileName'.
        Returns a dictionary containing a mapping
        of user names to a list preferred artists
    '''
    file = open(fileName, 'r')
    userDict = {}
    for line in file:
        # Read and parse a single line
        [userName, bands] = line.strip().split(":")
        bandList = bands.split(",")
        bandList.sort()
        userDict[userName] = bandList
    file.close()
    return userDict

def getPrefs(userName,userMap):
    '''returns the preferences of a user'''
    newPref = ""
    if userName in userMap:
        prefs = userMap[userName]
    else:
        print "This user is not currently in the database, please enter a different user"
        createMenu(userMap)
    prefs.sort()
    return prefs
def getPreferences(userName, userMap):
    ''' Returns a list of the uesr's preferred artists.

        If the system already knows about the user,
        it gets the preferences out of the userMap
        dictionary and then asks the user if she has
        additional preferences.  If the user is new,
        it simply asks the user for her preferences. '''
    newPref = ""
    if userName in userMap:
        prefs = userMap[userName]
        print("I see that you have used the system before.")
        print("Your music preferences include:")
        for artist in prefs:
            print(artist)
        print("Please enter another artist or band that you")
        print("like, or just press enter")
        newPref = raw_input("to proceed to the menu: ")
    else:
        prefs = []
        print("I see that you are a new user.")
        print("Please enter the name of an artist or band")
        newPref = raw_input("that you like: " )
        
    while newPref != "":
        prefs.append(newPref.strip().title())
        print("Please enter another artist or band that you")
        print("like, or just press enter")
        newPref = raw_input("to proceed to the menu: ")
        
    # Always keep the lists in sorted order for ease of
    # comparison
    prefs.sort()
    return prefs


def getRecommendations(currUser, prefs, userMap):
    ''' Gets recommendations for a user (currUser) based
        on the users in userMap (a dictionary)
        and the user's preferences in pref (a list).
        Returns a list of recommended artists.  '''
    bestUser = findBestUser(currUser, prefs, userMap)
    recommendations = drop(prefs, userMap[bestUser])
    return recommendations

def findBestUser(currUser, prefs, userMap):
    ''' Find the user whose tastes are closest to the current
        user.  Return the best user's name (a string) '''
    users = userMap.keys()
    bestUser = None
    bestScore = -1
    for user in users:
        score = numMatches(prefs, userMap[user])
        if score > bestScore and currUser != user:
            bestScore = score
            bestUser = user
    return bestUser

def drop(list1, list2):
    ''' Return a new list that contains only the elements in
        list2 that were NOT in list1. '''
    list3 = []
    i = 0
    j = 0
    while i < len(list1) and j < len(list2):
        if list1[i] == list2[j]:
            i += 1
            j += 1
        elif list1[i] < list2[j]:
            i += 1
        else:
            list3.append(list2[j])
            j += 1
    
    return list3

def numMatches( list1, list2 ):
    ''' return the number of elements that match between
        two sorted lists '''
    matches = 0
    i = 0
    j = 0
    while i < len(list1) and j < len(list2):
        if list1[i] == list2[j]:
            matches += 1
            i += 1
            j += 1
        elif list1[i] < list2[j]:
            i += 1
        else:
            j += 1
    return matches

def saveUserPreferences(userName, prefs, userMap, fileName):
    ''' Writes all of the user preferences to the file.
        Returns nothing. '''
    userMap[userName] = prefs
    file = open(fileName, "w")
    for user in userMap:
        toSave = str(user) + ":" + ",".join(userMap[user]) + \
                    "\n"
        file.write(toSave)
    file.close()    

def main():
    ''' The main recommendation function '''
    userMap = loadUsers(PREF_FILE)
    print("Welcome to the music recommender system!")

    createMenu(userMap)

if __name__ == "__main__": main()
