// Credit Card Checker & Validator, By Roberto Thompson

#include <cs50.h>
#include <math.h>
#include <stdio.h>

int main(void)
{

    // initalizes the variables long
    long num, originalNum;

    // initalizes the int variables setting to 0 and unassigned (digit)
    int checksum = 0;
    int digit, pos = 0;

    // prompting user for input (card number)
    do
    {
        num = get_long("Number: ");
        originalNum = num;
    }

    // sets the condition that the number prompted cannot be less then 0, and will keep prompting
    // the user for a higher number that is greater
    while (num < 0);

    // as the number is higher then 0
    while (num > 0)
    {

        // make the digit equal to the num mod 10
        digit = num % 10;

        // if (0 % 2 is not equal to 0) then (for 1 digit coming out of "digit", at a time)
        if (pos % 2 != 0)
        {

            // multiply the digit by 2
            digit *= 2;

            // if this has 2 digits then
            if (digit > 9)
            {
                // split the digit into seperates (ex. xx = x + x)
                digit = (digit % 10) + 1;
            }
        }
        // adds the digit to the checksum since it will be added no matter if it was or wasn't
        // multiplied by 2 earlier (its gonna get added anyways)
        checksum += digit;

        // divide the original num by 10 (since the mod is excluded to digit)
        num /= 10;

        // increase "pos"
        pos++;
    }

    // if the last digit of the number provided is equal to 0 then
    if (checksum % 10 == 0)
    {

        // first two digits are initalized to the number divided by the finalized pos (the digits
        // that were counted in the card) - 2
        long firstTwoDigits = originalNum / (long) pow(10, pos - 2);

        // if the digits are 34 or 37
        if (firstTwoDigits == 34 || firstTwoDigits == 37)
        {
            // print out AMEX
            printf("AMEX\n");
        }
        // if the digits are 51, 52, 53, 54, 55
        else if (firstTwoDigits >= 51 && firstTwoDigits <= 55)
        {
            // print out MASTERCARD
            printf("MASTERCARD\n");
        }

        // if the original num has a starting num of 4
        else if ((originalNum / (long) pow(10, pos - 1)) == 4)
        {

            // print out VISA
            printf("VISA\n");
        }
        else
        {

            // if none apply print out valid
            printf("INVALID\n");
        }
    }
    else
    {

        // if the checksum is not equal then print out invalid
        printf("INVALID\n");
    }
}
