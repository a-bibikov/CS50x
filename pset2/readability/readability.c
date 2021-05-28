#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int main(void)
{
    //variables init
    int letters = 0;
    int words = 0;
    int sentences = 0;
    float index = 0;

    float L = 0;
    float S = 0;

    //get string and string's length
    string s = get_string("Text: ");
    int length = strlen(s);

    //check every symbol
    for (int i = 0; i < length; i++)
    {
        if (isalpha(s[i]))
        {
            letters++;
        }
        else if (s[i] == ' ')
        {
            words++;
        }

        if (s[i] == '.' || s[i] == '!' || s[i] == '?')
        {
            sentences++;
        }
    }
    words = words + 1;

    //calculate constants
    L = (float) letters * 100 / (float) words;
    S = (float) sentences * 100 / (float) words;

    //calculate GRADE index
    index = round(0.0588 * L - 0.296 * S - 15.8);

    //print result by index
    if (index >= 0 && index < 16)
    {
        printf("Grade %i\n", (int) round(index));
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Before Grade 1\n");
    }
}