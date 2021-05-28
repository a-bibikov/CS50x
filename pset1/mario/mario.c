#include <cs50.h>
#include <stdio.h>

//some trick for right order
void mario(int);

//our main func
int main(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);
    for (int i = 0; i < n; i++)
    {
        mario(n - i - 1);
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        printf("  ");
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}

//alt func for alingment with spaces
void mario(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf(" ");
    }

}