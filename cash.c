// Coin Change Calculator, By Roberto Thompson
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // initializes the variables being used
    int cents, sum, quarters, dimes, nickels, pennys;

    // prompts the user for the change owed
    do
    {
        cents = get_int("Change owed: ");
    }

    // initializes the condition that cents cannot be less than 0 and will kept prompting the user
    // until it is > 0
    while (cents < 0);

    // shows how many quarters that will be used after dividing by cents (if any)
    quarters = cents / 25;

    // multiplies how many quarters that are used that will influence how many quarters is needed
    // for the cents prompted by the user (change owed)
    cents -= quarters * 25;

    // shows how many dimes that will be used after dividing by cents (if any)
    dimes = cents / 10;

    // multiplies how many dimes that are used that will influence how many dimes is needed for the
    // cents prompted by the user (change owed)
    cents -= dimes * 10;

    // shows how many nickels that will be used after dividing by cents (if any)
    nickels = cents / 5;
    // multiplies how many nickels that are used that will influence how many nickels is needed for
    // the cents prompted by the user (change owed)
    cents -= nickels * 5;

    // shows how many pennys that will be used after dividing by cents (if any)
    pennys = cents / 1;
    // multiplies how many pennys that are used that will influence how many pennys is needed for
    // the cents prompted by the user (change owed)
    cents -= pennys / 1;

    // totals the value of how many coins are used to conduct how much change is owed
    sum = quarters + dimes + nickels + pennys;

    // placeholds the variable for the sum of change owed in cents, and uses the function sum to do
    // that
    printf("%i\n", sum);
}
