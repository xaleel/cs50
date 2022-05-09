// Implements a dictionary's functionality
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Choose number of buckets in hash table
const unsigned int N = 182;

// Hash table
node *table[N];

bool search(node *head, const char *word)
{
    char *tempword = malloc(strlen(word) + 1);
    strcpy(tempword, word);
    for (int i = 0; i < strlen(word); i++)
    {
        tempword[i] = tolower(tempword[i]);
    }
    node *current = head;
    while (current != NULL)
    {
        if (strcmp(current->word, tempword) == 0)
        {
            free(tempword);
            return true;
        }
        current = current->next;
    }
    free(tempword);
    return false;
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    if (search(table[hash(word)], word))
    {
        return true;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    char post = toupper(word[0]);
    int pos = (post - 65) * 7; //7 positions for each letter
    switch (toupper(word[1])) //check for most common second letters; pos[relative 0] for other second letters
    {
        case 'E':
            pos++;
            break;
        case 'O':
            pos += 2;
            break;
        case 'H':
            pos += 3;
            break;
        case 'A':
            pos += 4;
            break;
        case 'I':
            pos += 5;
            break;
        case 'N':
            pos += 6;
            break;
    }
    return pos;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *dic = fopen(dictionary, "r"); //open dictionary file
    if (dic == NULL)
    {
        printf("can't fopen dictionary");
        return false;
    }
    char tempword[LENGTH];
    while (fscanf(dic, "%s", tempword) && feof(dic) == 0)
    {
        int hsh = hash(tempword);
        node *tword = malloc(sizeof(node));
        int len = strlen(tempword);
        for (int i = 0; i <= len; i++)//copy tempword to the node tword
        {
            tword->word[i] = tempword[i];
        }
        tword->next = table[hsh];//pointer in node points at the first element in the table
        table[hsh] = tword;//pointer in table now points at the new node instead
    }
    fclose(dic);
    //-------------print all hash table-----------
    // for(int i = 0; i<N; i++) {
    //     if(table[i] != NULL)
    //         printf(" (%s)",table[i]->word);
    //     else
    //         printf(" ~~ ");
    // }
    // printf("\n");
    //--------------------------------------------
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    int size = 0;
    for (int i = 0; i < N; i++)
    {
        node *current = table[i];
        while (current != NULL)
        {
            size++;
            current = current->next;
        }
    }
    return size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *temp;
    node *cr;
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            // free last node
            cr = table[i];
            while (cr != NULL)
            {
                temp = cr->next;
                free(cr);
                cr = temp;
            }
        }
    }
    return true;
}
