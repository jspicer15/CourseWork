# Welcome!

# In the following, you will have a small tutorial provided by Juno.
# Minor modifications in the following section were made by Fabian
# Foerg for CS306. At the end of this file, you will find another
# tutorial with further commands that are useful for CS306

# This is a regular file, which you can edit as much as you want,
# then save for later or discard. You can open a fresh copy by
# pressing `Ctrl-Space` and typing `tutorial` followed by `Enter`.

# (and if you remember one thing, make it `Ctrl-Space` – you can
# get to everything in Juno via the command bar that pops up)

# Go to the `View->Console` menu to see any output. If you have
# issues, please let me know at http://discuss.junolab.org/
# ––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––

# Update your packages before you start working
Pkg.update()

# In Juno we'll be using the Julia language. This is a Julia file and
# lines beginning with `#` are comments.

# Here's a very simple code block:

3 * 6 + 4

# We can evaluate code by right clicking on it and selecting "Evaluate".
# You should see the result, "22", pop up next to the code.

# It's quicker to use Ctrl-Enter (or Cmd-Enter on Mac). Try adding "+2"
# to this line and then evaluating.

2

# We can also define our own functions, such as this one which doubles a
# number:

function double(x)
  return 2x
end

# Click anywhere on the function definition and press `Ctrl-Enter`
# again. You should see a tick pop up next to the "end" to show that
# the function has been defined.

# Now we can call our function:

double(25)

# After evaluating this you should see the result "20" pop up. You may
# also notice that the "10" becomes underlined. Try clicking and
# dragging it from side to side to double another number.

# We can do more advanced things, like dealing with matrices. Try

x = rand(5, 5)

# If you evaluate this you'll see "Matrix Float64, 5×5" pop up next to it.
# A bold header like this indicates that you can click on the box
# to expand it and see the whole matrix.

# If you're not sure what a function does it's easy to find out. Just right
# click on the function's name (like "rand" above) and click "Toggle Docs".
# The shortcut for this is Ctrl-D. You can also remove the documentation
# by right clicking and selecting "Remove result".

# Let's try out some plotting. Start by loading the Gadfly package; if you
# type `using` you'll see a list of available packages in the autocomplete.

# You have to install the Gadfly package first using the following command:
Pkg.add("Gadfly")
using Gadfly

# A few simple examples; if you want to learn more about Gadfly, check out
# http://www.gadflyjl.org/

# A simple scatter plot:
plot(x = rand(10), y = rand(10))

# Let's try a random walk:
plot(x = 1:100, y = cumsum(rand(100)-0.5), Geom.point, Geom.line)

# And smooth it out:
plot(x = 1:100, y = cumsum(rand(100)-0.5), Geom.point, Geom.smooth)

# We can plot functions:
plot(x -> x^3 - 9x, -5, 5)
plot([sin, cos], 0, 6)
# (and remember to try sliding the values up and down here, too)

# Ok, Let's try something more interesting. We'll need to install and
# load the Images.jl package.

Pkg.add("Images")
using Images

# Let's try visualising this function. You can type latex symbols by
# typing a `\` and selecting from the autocomplete, e.g. `\phi` or `\le`.

# You can use `Shift-Enter` to quickly evaluate definitions.

const ϕ = golden

function foo(z)
  c = (φ-2)+(φ-1)im
  max = 80
  for n = 1:max
    abs(z) ≥ 2 && return n-1
    z = z^2 + c
  end
  return max
end

# Let's try this out – play around with the numbers!

foo(0)
foo(0.1+0.5im)

# Let's apply foo to a grid of numbers. Don't worry too much if you don't
# understand this code, but make sure to evaluate it. (Bonus points for
# using that Ctrl-D trick here, though)

foo(x, y) = foo(x + y*im)

foo_grid(n) =
  broadcast(foo,
            linspace(-0.5, 1, n)',
            linspace(-1, 0.5, n))

# Can you see the pattern?

foo_grid(10)

# Let's try it as an image:

convert(Image, scale(foo_grid(500), 1/80))

# It's a Julia set, of course!

# If you expand the image you can also click on the `Dictionary`
# field to see some interesting properties about it (if that's the
# kind of thing that floats your goat).

# If you want to learn more about Julia, take a look at
# http://julialang.org/learning/

# There is also the Julia manual and the Juno documentation, both
# of which are available from the help menu above.

# Enjoy!

# ––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
# In the following, we present a small tutorial for CS306.
# Run the commands (Ctrl-Enter in Juno) to see what the output is!
# Also, make sure to activate your conole (Ctrl-` in Juno) to display
# console output.
# To view documentation for a function, press Ctrl-D in Juno or
# run help(commandname) and view the console output.

# Tutorials on which this tutorial is based (recommended references for Julia):
#
# Official Julia documentation: http://docs.julialang.org/en/release-0.3/manual/getting-started/
# Plotting and notebooks: https://github.com/stevengj/julia-mit/
# Teaching material: http://julialang.org/teaching/
# Learn X in Y minutes where X=Julia: http://learnxinyminutes.com/docs/julia/

# Basic Math Operations

3 + 4
4 - 3
3 * 5
3.1 * 55.555
6 / 3
15 / 7
div(15, 7)
7 \ 15
help(div)
mod(5, 3)
5 % 3
mod(-5, 3)
-5 % 3
2^60
2^66
b1 = BigInt(2)
pow1 = b1^66
typeof(pow1)
sqrt(5)
(3 + 5im)^2
pi + e

# Bitwise Operations and Binary Numbers

x = 0x02F3
~x
y = 0x2F03
x | y
x & y
x $ y # XOR
8 >> 2
-8 >> 2
-8 >>> 2
8 << 2

bitstring = bits(21)
println(bitstring)
parseint("10101", 2)
parse("0b10101")

# Data Types

str1 = "ASDF"
typeof("ASDF")
'a'
typeof('a')
str1[2]
str1[2:end]
'C' - 'A'
int('A') # cast to int
char(69) # cast to char

true == false
true != false
true && true
false || true

horarray1 = [2 3 5]
verarray1 = [2, 3, 5]
push!(verarray1, 10)
append!([1, 2], [5, 10])

pop1 = pop!([2, 3, 5])
shift1 = [2, 3, 5, 7]
shift!(shift1)
shift1
unshift!(shift1, 2)

unsorted = [4, 2, 8, 1]
sorted = sort(unsorted)
unsorted
sort!(unsorted) # in place
unsorted

splice1 = [5, 8, 3 ,7]
splice!(splice1, 2)
splice1

matrix1 = [2 3 5; 4 8 2]
zeros(4)
ones(3)
ones(typeof(1), 3)
ones(Uint8, 3)

range1 = 32:99
range1[2]

typeof(32:99)
fromrange = [2:5]
length(fromrange)

tuple1 = (2, 4, 40)
tuple1[2:end]
tuple1[2]

in(40, tuple1)

a, b = 3, 5
a

cell(4, 2)

dict1 = Dict()
merge!(dict1, ["a" => 2, "x" => 5])

haskey(dict1, "x")
dict1["x"]

set1 = Set(2, 3, 4, 4)
push!(set1, 10)
in(10, set1)

# Functions and Control Structures

function myFunc(a, b)
  c = 10
  return a + b + c
end
myFunc(1, 2)

function defaultArg(a, b=20)
  return a + b
end
defaultArg(10)

defaultArg(10,1)

function printTimes(str, times)
  for i=1:times
    println(str)
  end
end
printTimes("HELLOWORLD", 10)

function printTimesWhile(str, times)
  if times < 1
    throw(DomainError())
  end
  i = times
  while i >= 1
    println(str)
  i = i - 1
  end
end
printTimesWhile("HELLOWORLD", 3)

function mySign(x)
  s = ""
  if x < 0
    s = "negative"
  elseif x == 0
    s = "zero"
  else
    s = "positive"
  end
  s
end
mySign(-3)
mySign(0)
mySign(2)

function multiReturn(a)
  return (a, a + 10)
end
multiReturn(1)

function arrayReturn(a)
  return [a, a + 10]
end
arrayReturn(1)

function myreverse(s::String)
  reverse(s)
end
myreverse("asdf")

for x in ["asdf", 3, 4]
  println(string(x))
end

# preferred way to iteratore over characters in a string
for character in "MYSTRING"
  println(character)
end

for (k, v) in [ "x" => 2, "y" => -3, "z" => 4 ]
  println(string(k, " is the key for ", v))
end

(x -> x + 10) (5) # evaluate lambda expression

function curry(x)
  function inner(y)
    return 3 + 2 * x - y
  end
  # returns a function
  inner
end
curry(3) # result is function
curry(3)(100)

function maybeexception(x)
  if x < 0
    error("x must not be negative!")
  end
  x + 1
end
maybeexception(10)

try
  maybeexception(-10)
catch e
  println(e)
end

# Library Functions

help(rand)
rand(1:100)
rand(1:100)
rand((4, 2))

sort([2, 5, 20])
sort([2, 5, 20], rev=true)

permute!([2, 5, 10], [2, 3, 1])
invperm([2, 3, 1])
ipermute!([2, 5, 10], [2, 3, 1])

map(x -> x + 10, [2:5])
filter(x -> x > 10, [-1:20])
reduce(+, [1:5])

# Types

typeof(0xABCD)
typeof(0xABABABABABABAB)
typemax(123)
typeof(-123)
int32(-123)

super(Int64)
super(super(Int64))
issubtype(Int,Real)

type Rectangle{T<:Real}
  a::T
  b::T
end

# It is idiomatic to define class methods separately from the class definition.

function area(r::Rectangle)
  return r.a * r.b
end

rect1 = Rectangle(2.0, 3.5)
area(rect1)

# Functions on Strings and Characters

int('A')
'C' - 'A'
'A' + 3
char(int('A') + 3)

for c in "CS306"
  println(c)
end

# concatenate characters
s = ""
for c in "CS306"
  if isalpha(c)
    s = string(s, c)
  end
end
s

# Converting from bytes to strings
uint8array = Uint8[ 'A', 'B', 'C' ]
append!(uint8array, [0x45, 0x42])
astring = ASCIIString(uint8array)
astring.data

# printing without newline at the end
print('C')
print('S')
print('\n')

# printing a line
println("CS")

# printing variable values
x = 42
println("I am printing ", x, " within a sentence.")

# Convert strings to BitArray instance and operate on BitArray
function stringToBits(s::ASCIIString)
  # turn each string character to an int and pack the ints
  # into a BitArray{1}
  bitpack(map(x -> x - '0', s.data))
end

# Convert a BitArray to a string
function bitsToString(ba::BitArray{1})
  # turn each bit into a string and concatenate the strings
  # 'string' is the string function below
  reduce(string, map(x -> if x "1" else "0" end, ba))
end

# Compute the bit-wise AND of two BitArray instances
function f(r::BitArray{1}, k::BitArray{1})
  if length(r) != length(k)
    error("r and k must have the same length!")
  end
  r & k
end

# Apply the newly defined functions
r = stringToBits("0101")
k = stringToBits("0011")
f(r, k)
