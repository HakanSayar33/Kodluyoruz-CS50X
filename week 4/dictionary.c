#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "dictionary.h"
#include <stdlib.h>

#define N 26

typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

node *hashtable[N];

int wordNum;

unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}

void makeLower(char *word)
{
    for (int i=0; i<LENGTH+1 ; i++)
    {
        if (word[i] == '\0') break;
        word[i] = tolower(word[i]);
    }
}

bool load(const char *dictionary)
{
    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    wordNum = 0;

    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    char word[LENGTH + 1];

    while (fscanf(file, "%s", word) != EOF)
    {
        wordNum++;
        node* temp = hashtable[hash(word)];
        if (!temp)
        {
            temp = (node*)malloc(sizeof(node));
            makeLower(word);
            strcpy(temp->word,word);
            temp->next = NULL;
            hashtable[hash(word)] = temp;
        }
        else {
            while(temp->next) temp = temp->next;
            temp->next = (node*)malloc(sizeof(node));
            makeLower(word);
            strcpy(temp->next->word,word);
            temp->next->next = NULL;
        }
        for (int i=0; i<LENGTH+1 ; i++) word[i] = '\0';
    }

    fclose(file);

    return true;
}

unsigned int size(void)
{
    if (wordNum) return wordNum;
    return 0;
}

bool check(const char *word)
{
    char word2[LENGTH+1];
    strcpy(word2,word);
    makeLower(word2);
    node* temp = hashtable[hash(word2)];
    while (temp)
    {
        if (strcmp(temp->word,word2) == 0) return true;
        temp = temp->next;
    }
    return false;
}

bool unload(void)
{
    for (int i=0; i<N ; i++){
        node* temp = hashtable[i];
        while (temp)
        {
            node* temp2 = temp->next;
            free(temp);
            temp = temp2;
        }
    }
    return true;
}
