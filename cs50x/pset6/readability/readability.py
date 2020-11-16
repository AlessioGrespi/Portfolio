import string
from cs50 import *

h = get_string("Text: ")
list = []
stops = []

for letters in h:
    if letters == " " or letters in string.punctuation:
        list.append(letters)
    if letters == "." or letters == "?" or letters == "!":
        stops.append(letters)
    
    stop = len(stops)
    letters = len(h) - len(list)
    words = len(h.split())

L = (letters / words) * 100
S = (stop / words) * 100
index = round(0.0588 * L - 0.296 * S - 15.8)
if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print("Grade: %i" % (index))