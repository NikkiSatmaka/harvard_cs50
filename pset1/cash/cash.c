// Greedy algorithm
// Find the fewest amount of coins
#include <cs50.h>
#include <math.h>
#include <stdio.h>

float get_positive_float(void);

int main(void)
{
    float dollars = get_positive_float();
    int cents = round(dollars * 100);

    int sum_coins = 0;

    // Use up all the quarters
    sum_coins += cents / 25;
    cents %= 25;

    // Use up all the dimes
    sum_coins += cents / 10;
    cents %= 10;

    // Use up all the nickles
    sum_coins += cents / 5;
    cents %= 5;

    // Use up all the pennies
    sum_coins += cents / 1;
    cents %= 1;

    printf("%i\n", sum_coins);
}

// Prompt user for positive float
float get_positive_float(void)
{
    float n;
    do
    {
        n = get_float("Change owed: ");
    }
    while (n < 0);
    return n;
}