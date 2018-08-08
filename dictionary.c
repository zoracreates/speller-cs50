// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>

#include "dictionary.h"
#include "hash.h"

// Global variables
node *hashtable[HASHTABLE_SIZE];
int word_count = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    if (word != NULL)
    {
        // convert word to lowercase and store it
        int word_len = strlen(word);
        char word_lower[word_len + 1];
        for (int i = 0; i < word_len; i++)
        {
            word_lower[i] = tolower(word[i]);
        }

        // add null terminator to end of char array
        word_lower[word_len] = '\0';

        // find where in the array the word ould be
        int word_loc = hash_it(word_lower);

        // iterate through the hash talble
        node *cursor = hashtable[word_loc];
        while (cursor != NULL)
        {
            if (strcasecmp(word_lower, cursor->word) == 0)
            {
                return true;
            }
            cursor = cursor->next;
        }

        // if word is not found, return false
        return false;
    }
    return true;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // open dictionary
    FILE *dict_file = fopen(dictionary, "r");
    if (dict_file == NULL)
    {
        return false;
    }
    char dict_word[LENGTH + 1];
    while (fscanf(dict_file, "%s", dict_word) != EOF)
    {
        // allocate spece for a new node
        node *new_node = calloc(1, sizeof(node));
        if (new_node == NULL)
        {
            unload();
            return false;
        }
        strcpy(new_node->word, dict_word);

        // hash word with hash function
        int hash_num = hash_it(new_node->word);

        // place new node in current array per hash function
        if (hashtable[hash_num] == NULL)
        {
            hashtable[hash_num] = new_node;
        }
        else
        {
            // update pointer first if  hashtable is not empty
            new_node->next = hashtable[hash_num];
            hashtable[hash_num] = new_node;
        }
        word_count++;
    }
    fclose(dict_file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (word_count > 0)
    {
        return word_count;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // iterate through the hash table
    for (int i = 0; i < HASHTABLE_SIZE - 1; i++)
    {
        // iterate through the linked list in the hashtable array
        while (hashtable[i] != NULL)
        {
            // point to the node to be freed
            node *temp = hashtable[i];
            // update cursor as to not lose position
            hashtable[i] = temp->next;
            // free node
            free(temp);
        }
    }

    // indicate unload as successful
    return true;
}
