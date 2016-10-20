# Matrix class
# January 26, 2010
# RLH

from Vector import *

class Matrix:
    """ 2x2 matrix class """

    def __init__(self, a11=0, a12=0, a21=0, a22=0):
        self.array = [[a11, a12], [a21, a22]]

    def set(self, row, column, value):
        """Set element at row and column to given value"""
        self.array[row][column] = value

    def get(self, row, column):
        """Get value at given row and column"""
        return self.array[row][column]

    def __add__(self, other):
        result = Matrix()
        for row in range(0, 2):
            for col in range(0, 2):
                result.set(row, col, self.get(row, col) + other.get(row, col))
        return result

    def __mul__(self, other):
        """ if other is a Matrix, returns a Matrix.  If other is a Vector, returns a Vector."""
        if other.__class__.__name__ == "Matrix":
            result = Matrix()
            for row in range(0, 2):
                for col in range(0, 2):
                    # Compute result matrix in the given row and col
                    entry = 0
                    for i in range(0, 2):
                            entry += self.get(row, i) * other.get(i, col)
                    result.set(row, col, entry)
            return result
        elif other.__class__.__name__ == "Vector":
            result = Vector()
            x = self.get(0, 0) * other.x + self.get(0, 1) * other.y
            y = self.get(1, 0) * other.x + self.get(1, 1) * other.y
            return Vector(x, y)
        else:
            print "Can't multiply a matrix by a ", other.__class__.name__, "!!!"  # !!! is a nice touch

    def __repr__(self):
        return str(self.array[0][0]) + " " + str(self.array[0][1]) + "\n" + str(self.array[1][0]) + " " + str(self.array[1][1])
