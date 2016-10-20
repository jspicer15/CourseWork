# test3_Q56 - questions 5 and 6 on third exam, 2014
# John Spicer
# I pledge my honor that I have abided by the Stevens Honor System

###########################################################################
# RULES: you can use Moodle to download this file and upload your solution.
# You can use IDLE to edit and run your program.  You should NOT look at 
# other programs in IDLE, you should NOT use any other programs, and you 
# should NOT use any notes or books.
# According to the Honor Code, you should report any student who appears
# to be violating these rules.
###########################################################################

'''This section tests your knowlegde of OOP with classes in Python.
We have a Track class that stores data about audio tracks (songs) and a
PlayList class that manages a list of Tracks.'''

########################
# Question 5 (15 points)
# Implement the missing sections in the Track class.
########################
class Track(object):
    def __init__(self, title, artist, minutes, seconds):
        '''Initializes PRIVATE fields with the same name as those
           passed in as arguments.
           title and artist will be passed in as strings.
           minutes and seconds will be passed in as integers.
           seconds will be between 0 and 59.
           '''
        self.__title = title
        self.__artist = artist
        self.__minutes = int(minutes)
        self.__seconds = int(seconds)

    def length_as_str(self):
        '''Returns the length of the track as a string.
           Example:
              A track of 4 minutes and 22 seconds should be "4:22"
              A track of 3 minutes and 9 seconds should be "3:09"
              (note the leading 0 for the seconds portion)
        '''
        if self.__seconds < 10:
            return str(self.__minutes) + ':' + str(0) + str(self.__seconds)
        else:
            return str(self.__minutes) + ':' + str(self.__seconds)

    def length_in_seconds(self):
        '''Returns the length of the track in seconds.'''
        return (self.__minutes * 60) + self.__seconds

    def __str__(self):
        '''Returns a string representation of the track.'''
        return self.__title + ': ' + self.__artist + ' (' + \
               self.length_as_str() + ')'

########################
# Question 6 (15 points)
# Implement the missing sections in the PlayList class.
########################
class PlayList(object):
    def __init__(self):
        '''Initializes PRIVATE field track_list to an empty list.'''
        self.__track_list = []

    def add_track(self, track):
        '''Adds a track to the playlist's list of tracks.'''
        self.__track_list =  self.__track_list + [track]

    def get_longest_track(self):
        '''Returns the longest track in the playlist.
           You may assume that the playlist contains at least 1 track.
           Use method length_in_seconds() in the Track class in your
           algorithm below.'''
        longest = ''
        for track in self.__track_list:
            if longest == '':
                longest = track
            elif track.length_in_seconds() > longest.length_in_seconds():
                longest = track
        return longest
            

    def __str__(self):
        '''Returns a string representation of the playlist.'''
        s = ''
        for track in self.__track_list:
            s += str(track) + '\n'
        return s

t0 = Track('The Heart Wants What It Wants', 'Selena Gomez', 4, 35)
t1 = Track('Shake It Off', 'Taylor Swift', 4, 1)
t2 = Track('All About That Bass', 'Meghan Trainor', 3, 10)
t3 = Track('Animals', 'Maroon 5', 3, 49)
t4 = Track('Am I Wrong', 'Nico & Vinz', 5, 4)
t5 = Track('Stay With Me', 'Sam Smith', 3, 29)
t6 = Track('Roar', 'Katy Perry', 4, 29)
t7 = Track('Love Me Harder', 'Ariana Grande & The Weeknd', 4, 11)
t8 = Track('Thinking Out Loud', 'Ed Sheeran', 4, 56)
t9 = Track('We Can''t Stop', 'Miley Cyrus', 3, 33)

def simple_test():
    playlist = PlayList()
    playlist.add_track(t1)
    playlist.add_track(t5)
    playlist.add_track(t7)
    assert str(playlist) == 'Shake It Off: Taylor Swift (4:01)\n' + \
                            'Stay With Me: Sam Smith (3:29)\n' + \
                            'Love Me Harder: Ariana Grande & The Weeknd (4:11)\n'
    print 'Playlist matches.'
    assert str(playlist.get_longest_track()) == \
                            'Love Me Harder: Ariana Grande & The Weeknd (4:11)'
    print 'Longest track matches.'

if __name__ == '__main__':
    simple_test()
    # Feel free to write more of your own tests here.


