from cs50 import get_int

# get height value from input
height = get_int("Height: ")

# check height value from 1 to 8
if height < 1 or height > 8:
    height = get_int("Height: ")

# print each line in heigth
for i in range(height):
    hashes = i + 1
    print(" " * (height - i - 1) + "#" * hashes + "  " + "#" * hashes)