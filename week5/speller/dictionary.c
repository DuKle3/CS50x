// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <strings.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26 * 26 * 26;

// global variables for counting
unsigned int count = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // get the hash val
    int index = hash(word);
    // go into the hash table
    node *cursor = table[index];
    while (cursor != NULL)
    {
        // go through the linked strcasecmp the word
        if (!strcasecmp(cursor->word, word))
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned int tmp1 = word[0] ? (toupper(word[0]) - 'A') * 26 * 26 : 0;
    unsigned int tmp2 = word[1] ? (toupper(word[1]) - 'A') * 26 : 0;
    unsigned int tmp3 = word[2] ? (toupper(word[2]) - 'A') : 0;
    // check if \0 in first three char
    if (!word[1])
    {
        return tmp1;
    }
    if (!word[2])
    {
        return tmp1 + tmp2;
    }
    return tmp1 + tmp2 + tmp3;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // 1. Open dictionary file
    FILE *input = fopen(dictionary, "r");

    // 2. read string one at a time
    char *word = malloc(LENGTH);
    if (word == NULL)
    {
        return false;
    }

    while (fscanf(input, "%s", word) != EOF)
    {
        // 3. create a new node for each word
        node *new = malloc(sizeof(node));
        if (new == NULL)
        {
            return false;
        }

        // update the word
        strcpy(new->word, word);
        // initialize the pointer
        new->next = NULL;

        // 4. hash word --> hash value
        unsigned int index = hash(word);

        // 5. insert node to hash table
        new->next = table[index];
        table[index] = new;

        count++;
    }
    fclose(input);
    free(word);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // iterate the table
    for (int i = 0; i < N; i++)
    {
        // create the cursor
        node *cursor = table[i];
        while (cursor != NULL)
        {
            // tmp for remember current node (to free)
            node *tmp = cursor;
            // cursor go into next node
            cursor = tmp->next;
            free(tmp);
        }
    }

    return true;
}
