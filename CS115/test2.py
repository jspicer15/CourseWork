# CS 115 Test2 Q78 - Version B
##########################################################
# Name: John
# Date: 10/24/2014
# Pledge: I pledge my honor that I have abided by the Stevens Honor System
##########################################################


#############
# Question 7a
# Create a dictionary INT_TO_HEX_DIGIT than maps integers
# to their corresponding hexadecimal digits.
# 0 -> '0'
# 1 -> '1'
# ...
# 9 -> '9'
# 10 -> 'A'
# 11 -> 'B'
# ...
# 15 -> 'F'
#############

INT_TO_HEX_DIGIT = {
    0 : '0',
    1 : '1',
    2 : '2',
    3 : '3',
    4 : '4',
    5 : '5',
    6 : '6',
    7 : '7',
    8 : '8',
    9 : '9',
    10 : 'A',
    11 : 'B',
    12 : 'C',
    13 : 'D',
    14 : 'E',
    15 : 'F'
    }

#############
# Question 7b
# Create a dictionary HEX_TO_INT_NUMBER than maps hexadecimal
# digits to their corresponding integer values.
# '0' -> 0
# '1' -> 1
# ...
# '9' -> 9
# 'A' -> 10
# 'B' -> 11
# ...
# 'F' -> 15
############

HEX_TO_INT_NUMBER = {
    '0': 0,
    '1' : 1,
    '2' : 2,
    '3' : 3,
    '4' : 4,
    '5' : 5,
    '6' : 6,
    '7' : 7,
    '8' : 8,
    '9' : 9,
    'A' : 10,
    'B' : 11,
    'C' : 12,
    'D' : 13,
    'E' : 14,
    'F' : 15
    }


#############
# Question 8
# Implement the functions integer_to_hex_helper and hex_to_integer.
# Use recursion and use the dictionaries you defined for Question 7.
#
# Hint: read everything before starting to work.  
# The test code provides examples of what the functions should do.
#############

def integer_to_hex(num):
    '''Assume num is an integer.
       Convert it to a hexadecimal (base 16) string.'''

    def integer_to_hex_helper(num):
        '''Assume num is an integer.  Convert it to hexidecimal, without any
           leading zeros.  In particular, return the empty string for 0.'''

        if num == 0:
            return ''
        return integer_to_hex_helper(num/16) + INT_TO_HEX_DIGIT[num % 16]

    # We are calling your helper function to ensure there is no leading 0
    # in the return value.
    return '0' if num == 0 else integer_to_hex_helper(num)

def hex_to_integer(hex):
    '''Assume hex is a string that represents a number in base 16.
    Convert it to an integer.''' 
    def helpHex(hex,Y):        
        if hex == '':
            return 0
        elif hex[-1] == '0':
            return helpHex(hex[0:-1],Y+1)
        return helpHex(hex[0:-1],Y+1) + HEX_TO_INT_NUMBER[hex[-1]] * (16 ** Y)
    return helpHex(hex,0)


#############
# Test code.  
# Notice that hexidecimals are strings of characters, whereas integers are not.
#############

def test():
    '''Prints a success message, or assertion error if a test fails.'''
    assert integer_to_hex(0) == '0'
    assert integer_to_hex(7) == '7'
    assert integer_to_hex(11) == 'B'
    assert integer_to_hex(20) == '14'
    assert integer_to_hex(255) == 'FF'   # notice 255 is decimal notation for a integer
    assert integer_to_hex(1000) == '3E8'
    assert hex_to_integer('0') == 0
    assert hex_to_integer('A') == 10
    assert hex_to_integer('48321') == 295713
    assert hex_to_integer('DEADBEEF') == 3735928559
    assert hex_to_integer(integer_to_hex(10)) == 10 
    assert hex_to_integer(integer_to_hex(0)) == 0
    assert hex_to_integer(integer_to_hex(12345)) == 12345
    print "Tests were successful."

# test_composition()
