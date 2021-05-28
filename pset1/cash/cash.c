#include <cs50.h>
#include <stdio.h>
#include <math.h>

int quater = 25;
int dime = 10;
int nickel = 5;
int penny = 1;

int sum;

int main(void)
{

    float dollars;
    int coins = 0;
    do
    {
        dollars = get_float("Change owed: ");
    }
    while (dollars < 0);
    int cents = round(dollars * 100);

    do
    {
        if (cents >= quater)
        {
            cents = cents - quater;
            coins++;
        }
    }
    while (cents >= quater);

    do
    {
        if (cents >= dime)
        {
            cents = cents - dime;
            coins++;
        }
    }
    while (cents >= dime);

    do
    {
        if (cents >= nickel)
        {
            cents = cents - nickel;
            coins++;
        }
    }
    while (cents >= nickel);

    do
    {
        if (cents >= penny)
        {
            cents = cents - penny;
            coins++;
        }
    }
    while (cents >= penny);

    printf("%i\n", coins);
}