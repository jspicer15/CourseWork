# Shapes
# January 26, 2010
# RLH
# John Spicer
# I pledge my honor that I have abided by the Stevens Honor System
import math
import turtle

from Matrix import *
from Vector import *

class Shape:
    def __init__(self):
        self.points = []
        
    def render(self):
        """Use turtle graphics to render shape"""
        turtle.penup()
        turtle.setposition(self.points[0].x, self.points[0].y)
        turtle.pendown()
        turtle.fillcolor(self.color)
        turtle.pencolor(self.color)
        turtle.begin_fill()
        for vector in self.points[1:]:
            turtle.setposition(vector.x, vector.y)
        turtle.setposition(self.points[0].x, self.points[0].y)
        turtle.end_fill()

    def erase(self):
        """Draw shape in white to effectively erase it from screen"""
        temp = self.color
        self.color = "white"
        self.render()
        self.color = temp
    
    def rotate(self, theta, rotateAbout):
        """Rotate shape by theta degrees about the vector point rotateAbout. Please enter rotateAbout
        using the syntax Vector(xcoor,ycoor)"""
        theta = math.radians(theta)  # THIS IS CORRECT!
        # Python's trig functions expect input in radians
        # so this function converts from degrees into radians.
        if rotateAbout == Vector(0,0):
            RotationMatrix = Matrix(math.cos(theta), -1*math.sin(theta), math.sin(theta), math.cos(theta))
            NewPoints = []
            for vector in self.points:
                newvector = RotationMatrix * vector
                NewPoints.append(newvector)
            self.points = NewPoints
        else:
            Shape.translate(self,-rotateAbout)
                            
            RotationMatrix = Matrix(math.cos(theta), -1*math.sin(theta), math.sin(theta), math.cos(theta))
            NewPoints = []
            for vector in self.points:
                newvector = RotationMatrix * vector
                NewPoints.append(newvector)
            self.points = NewPoints
            Shape.translate(self,-rotateAbout)                
                            

    def translate(self, vec):
        '''shifts the points of a shape over the x and y units specificed in vector vec'''
        for vector in self.points:
            vector.x += vec.x
            vector.y += vec.y
        
        
class Rectangle(Shape):
    def __init__(self, width, height, center = Vector(0, 0), color = "black"):
        self.center = center
        SW = Vector(self.center.x - width/2.0, self.center.y - height/2.0)
        NW = Vector(self.center.x - width/2.0, self.center.y + height/2.0)
        NE = Vector(self.center.x + width/2.0, self.center.y + height/2.0)
        SE = Vector(self.center.x + width/2.0, self.center.y - height/2.0)
        self.points = [SW, NW, NE, SE]
        self.color = color

class Square(Rectangle):
    def __init__(self, width, center=Vector(0, 0), color = "orange"):
        Rectangle.__init__(self, width, width, center, color)
        
class Circle(Shape):
    def __init__(self, center = Vector(0, 0), radius = 10, color = "blue"):
        self.center = center
        self.radius = radius
        self.color = color

    def render(self):
        turtle.penup()
        turtle.setposition(self.center.x, self.center.y-self.radius)
        turtle.pendown()
        turtle.fillcolor(self.color)
        turtle.pencolor(self.color)
        turtle.begin_fill()
        turtle.circle(self.radius)
        turtle.end_fill()

    def rotate(self, theta,rotateAbout):
        """ theta is in degrees """
        if rotateAbout == Vector(0,0):
            theta = math.radians(theta)
            RotationMatrix = Matrix(math.cos(theta), -1*math.sin(theta), math.sin(theta), math.cos(theta))        
            self.center = RotationMatrix * self.center

        else:
            Circle.translate(self,-rotateAbout)
                            
            theta = math.radians(theta)
            RotationMatrix = Matrix(math.cos(theta), -1*math.sin(theta), math.sin(theta), math.cos(theta))        
            self.center = RotationMatrix * self.center

            Circle.translate(self,-rotateAbout)    

    def translate(self, vec):
        '''shifts the points of a shape over the x and y units specificed in vector vec'''
        self.center.x += vec.x
        self.center.y += vec.y

class Triangle(Shape):
    def __init__(self, center = Vector(0,0), length = 100, color = "green"):
        L = Vector(center.x - length, center.y - length * 1.73205080757)
        R = Vector(center.x + length, center.y - length * 1.73205080757)
        T = Vector(center.x , center.y + (length))
        self.points = [L,R,T]
        self.color = color

    def render(self):
        Shape.render(self)

def main():
    triangle = Triangle()
    triangle.render()
    triangle.translate(Vector(25,25))
    triangle.render()
    triangle.rotate(30,Vector(25,25))
    triangle.render()

    circle = Circle()
    circle.center = Vector(-275,250)
    circle.render()
    circle.translate(Vector(25,25))
    circle.render()
    circle.rotate(30,Vector(25,25))
    circle.render()

    rectangle = Rectangle(50,50)
    rectangle.render()
    rectangle.translate(Vector(25,25))
    rectangle.render()
    rectangle.rotate(30,Vector(25,25))
    rectangle.render()

    square = Square(10)
    square.render()
    square.translate(Vector(25,25))
    square.render()
    square.rotate(30,Vector(25,25))
    square.render()


if __name__ == "__main__":
    main()


        
