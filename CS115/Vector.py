# Vector class
# January 26, 2010
# RLH

import math

class Vector:
    def __init__(self, x=0, y=0):
        self.x = x
        self.y = y

    def magnitude(self):
        """ Returns magnitude of vector """
        return math.sqrt(self.x * self.x + self.y* self.y)

    def normalize(self):
        """ Sets vector magnitude to 1 """
        mag = self.magnitude()
        self.x = self.x/mag
        self.y = self.y/mag

    def __add__(self, other):
        return Vector(self.x + other.x, self.y + other.y)

    def __neg__(self):
        return Vector(-self.x, -self.y)

    def __sub__(self, other):
        return Vector(self.x - other.x, self.y - other.y)

    def __repr__(self):
        return "(" + str(self.x) + "," + str(self.y) + ")"

