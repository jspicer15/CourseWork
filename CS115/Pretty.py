from Shapes import *

    
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

#John Spicer
#I pledge my honor that I have abided by the Stevens Honor System
