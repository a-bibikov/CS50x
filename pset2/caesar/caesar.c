#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        for (int i = 0, k = strlen(argv[1]); i < k; i++)
        {
            if (!isdigit(argv[1][i]))
            {
                printf("Usage: %s key\n", argv[0]);
                return 1;
            }
        }

        //get string from user
        string text = get_string("plaintext: ");
        int length = strlen(text);

        //get cipher key
        int key = atoi(argv[1]);

        printf("ciphertext: ");
        //check each character
        for (int i = 0; i < length; i++)
        {
            if (isalpha(text[i]))
            {
                //if character is a letter
                if (isupper(text[i]))
                {
                    char c = (text[i] - 65 + key) % 26 + 65;
                    printf("%c", c);
                }
                else if (islower(text[i]))
                {
                    char c = (text[i] - 97 + key) % 26 + 97;
                    printf("%c", c);
                }
            }
            else
            {
                //if character is not a letter
                printf("%c", text[i]);
            }
        }
        printf("\n");

        //return success
        return 0;
    }
    else
    {
        printf("Usage: %s key\n", argv[0]);

        //return error
        return 1;
    }
}