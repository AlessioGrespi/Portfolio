from cs50 import get_int

while True:
    h = get_int("Height:\n")
    if h >= 1 and h <= 8:
        break
for i in range(0,h):
    steps = " " * (h-i) + "#" * (i+1)
    print(steps)
