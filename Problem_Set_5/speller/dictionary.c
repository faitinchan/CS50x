// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Size of the dictionary
unsigned int dict_size = 0;

void free_ptr(node *ptr);

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    unsigned int box = hash(word);
    node *ptr = table[box];
    while (ptr != NULL)
    {
        if (strcasecmp(word, ptr->word) == 0)
        {
            return true;
        }

        ptr = ptr->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        return false;
    }

    // Read each word in the file
    char c;
    int index = 0;
    node *ptr = NULL;
    while (fread(&c, sizeof(char), 1, source))
    {
        // Add each word to the hash table
        if (index == 0)
        {
            dict_size++;
            ptr = malloc(sizeof(node));
            if (ptr == NULL)
            {
                return false;
            }
            ptr->next = NULL;

            ptr->word[index] = c;
            index++;
        }
        else if (c == '\n')
        {
            ptr->word[index] = '\0';
            index = 0;

            unsigned int box = hash(ptr->word);
            if (table[box] == NULL)
            {
                table[box] = ptr;
                ptr = NULL;
            }
            else
            {
                ptr->next = table[box];
                table[box] = ptr;
                ptr = NULL;
            }
        }
        else
        {
            ptr->word[index] = c;
            index++;
        }
    }

    // Close the dictionary file
    fclose(source);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dict_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < 26; i++)
    {
        free_ptr(table[i]);
    }

    return true;
}

void free_ptr(node *ptr)
{
    if (ptr == NULL)
    {
        return;
    }
    else
    {
        free_ptr(ptr->next);
        free(ptr);
    }
}
