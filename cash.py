// Coin Change Calculator, By Roberto Thompson
from cs50 import get_float

# prompts the user
while True:
    cents = get_float("Change owed: ")
    if cents >= 0:
        break

cents = round(cents * 100)

# change in quarters
quarters = cents // 25
cents %= 25

# change in dimes
dimes = cents // 10
cents %= 10

# change in nickels
nickels = cents // 5
cents %= 5

# change in pennys
pennys = cents

# sum of all leftover change
sum = quarters + dimes + nickels + pennys

# prints total change due
print(f"{sum}")
