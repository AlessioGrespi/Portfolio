from cs50 import get_float

owed = get_float("Change Owed: ")
owed = round(owed * 100)

# quaters

quaters = owed // 25
left = owed- (25 * quaters)

# dimes

dimes  = left // 10
left2 = left-(10 * dimes )

# nickels

nickels = left2 // 5
left3 = left2-(5 * nickels)

# pennies

pennies = left3 // 1
left4 = left3-(1 * pennies)

print(quaters + dimes + nickels + pennies)