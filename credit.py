// Credit Card Checker & Validator, By Roberto Thompson
from cs50 import get_int

while True:
    num = get_int("Number: ")
    if num >= 0:
        break

digit = 0
pos = 0
checksum = 0
originalNum = num

while num > 0:
    digit = num % 10
    if pos % 2 != 0:
        digit *= 2
        if digit > 9:
            digit = digit % 10 + 1
    checksum += digit
    num //= 10  # Use integer division to avoid floating point issues
    pos += 1

if checksum % 10 == 0:
    firstTwoDigits = originalNum // (10 ** (pos - 2))
    if firstTwoDigits == 34 or firstTwoDigits == 37:
        print("AMEX")
    elif firstTwoDigits >= 51 and firstTwoDigits <= 55:
        print("MASTERCARD")
    elif originalNum // (10 ** (pos - 1)) == 4:
        print("VISA")
    else:
        print("INVALID")
else:
    print("INVALID")
