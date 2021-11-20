
from cs50 import get_int

while True:
    h = get_int("Height: ")
    if h >= 1 and h <= 8:
        break
    
for i in range(0,h):
    steps = " " * (h-i-1) + "#" * (i+1) + "  " + "#" * (i+1)
    print(steps)
    

    
"""
from cs50 import get_int
//ensure valid input; prompt user if h is <1 or >8
while True:
    h = get_int('height: ')
    if h < 1 or h > 8:
        h = get_int('height: ')
    if h >= 1 or h <= 8:
        break
// iterate through h
for i in range(h):
    print((h - 1 - i) * " ", end="")
    print((i + 1) * "#")

"""