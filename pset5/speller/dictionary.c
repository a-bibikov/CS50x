// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <stdio.h>
#include <stddef.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 45;
// init words counter
int wordsCounter = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int length = strlen(word);
    char tempWord[length + 1];

    tempWord[length] = '\0';

    for (int i = 0; i < length; i++)
    {
        tempWord[i] = tolower(word[i]);
    }

    int key = hash(tempWord) % N;

    node *nodePointer = table[key];
    if (nodePointer != NULL)
    {
        node *cursor = nodePointer;
        while (cursor != NULL)
        {
            if (strcmp(tempWord, cursor->word) == 0)
            {
                return true;
            }
            cursor = cursor->next;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    int value = 0;

    for (int i = 0; word[i] != '\0'; i++)
    {
        value += tolower(word[i]);
    }

    return value % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // open and read file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    char tempWord[LENGTH + 1];

    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }


    //while is the end of file
    while (fgets(tempWord, LENGTH + 2, file))
    {
        tempWord[strlen(tempWord) - 1] = '\0';

        int key = hash(tempWord) % N;

        node *tempNode = malloc(sizeof(node));

        if (tempNode == NULL)
        {
            fclose(file);
            return false;
        }

        strcpy(tempNode->word, tempWord);
        tempNode->next = table[key];
        table[key] = tempNode;

        wordsCounter++;
    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return wordsCounter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *nodePointer = table[i];

        while (nodePointer != NULL)
        {
            node *temp = nodePointer;
            nodePointer = nodePointer->next;
            free(temp);
        }

        table[i] = NULL;
    }
    return true;
}
