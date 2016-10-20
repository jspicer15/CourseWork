import sys

# demo_file_io.py
# Read and write operations on user preferences file.

# File format: Text file, one line per user.  Each line:
# username:artist1,artist2,...,artistN

# To process the file we need to:
# - split into lines
# - for each line, split at the colon, to get username and artists
# - split at commas to get artists
# - remove leading and trailing spaces, and convert all letters to lower case
#   (so comparisons work reasonably).

# Example of putting names in standard format
# example_artist = "  the clash of Death  "
# print example_artist.strip().lower()

# Note if we were to now:
# print example_artist
# it would still be "  the clash of Death  ", as strings
# are immutable and methods that operate on strings actually
# return new strings.

SAMPLE_FILE_CONTENT = \
'''dave:alanis Morrisset, Khaled, Michael Jackson
sue:Kate Bush,Nirvana,Michael Jackson'''

# Reading and printing a file.
def read_print_user_prefs(filename):
    '''Assume filename is path to an existing file in the format above.
       Print each user name and a list of the user's prefs.'''
    input_file = open(filename, 'r')   # Open the file for reading.
    for line in input_file:            # Get one line at a time.
        [user, artists] = line.split(':')
        artists = artists.split(',')
        for i in range(len(artists)):
            artists[i] = artists[i].strip()
        user = user.strip()
        print user + ' : ' + str(artists)
    input_file.close() # Important - do not forget to close the file

# Writing a file.
def write_prefs(filename):
    '''Open existing or new file named filename.
       Write SAMPLE_FILE_CONTENT to it.'''
    output_file = open(filename, 'w')
    lines = SAMPLE_FILE_CONTENT.split('\n') # split into lines, for sake of example
    for line in lines:
        output_file.write(line + '\n')
    output_file.close()

try:    
    read_print_user_prefs('input.txt')
except IOError as error:
    print error
    sys.exit(1)
write_prefs('output.txt')
sys.exit(0)
