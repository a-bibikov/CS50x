#include <cs50.h>
#include <stdio.h>

int main()
{
    long card_number = get_long_long("Number: ");
    int new_d = 0, x2 = 0, addsum = 0, x2prod = 0, sum = 0, digitstwo,  multiple;
	bool valide;
 
    while (card_number > 0)
    {
        x2 = new_d;
        new_d = card_number % 10;
 
        if (addsum % 2 == 0)
        {
            sum += new_d;
        }
        else
        {
            multiple = 2 * new_d;
            x2prod += (multiple / 10) + (multiple % 10);
        }
 
        card_number /= 10;
        addsum++;
    }
 
    valide = (sum + x2prod) % 10 == 0;
    digitstwo = (new_d * 10) + x2;
 
    if (new_d == 4 && addsum >= 13 && addsum <= 16 && valide)
    {
        printf("VISA\n");
    }
    else if (digitstwo >= 51 && digitstwo <= 55 && addsum == 16 && valide)
    {
        printf("MASTERCARD\n");
    }
    else if ((digitstwo == 34 || digitstwo == 37) && addsum == 15 && valide)
    {
        printf("AMEX\n");
    }
    else
    {
        printf("INVALID\n");
    }
}