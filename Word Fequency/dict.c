#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "dict.h"

#define DICT_PROLOG(pdict, newvar)                    \
    assert(pdict);                                    \
    Dict_list* newvar = *((Dict_list**) (pdict + 1));


typedef struct Dict_list
{
    char*             word;
    int               freq;
    struct Dict_list* next;    
} Dict_list;

void dict_addword(Dict* dr, char* wd);
void dict_print(Dict* dr);
void dict_destroy(Dict* dr);

Dict_list* dict_find(Dict_list* dls, char* wd);
void       dict_add(Dict* dr, char* wd);


Dict* dict()
{
    Dict* newdr = (Dict*) malloc(sizeof(Dict) + sizeof(Dict_list*));
    assert(newdr);

    newdr->addword = dict_addword;
    newdr->print   = dict_print;
    newdr->destroy = dict_destroy;

    Dict_list** dls = (Dict_list**) (newdr + 1);
    *dls = NULL;

    return newdr;
}


void dict_addword(Dict* dr, char* wd)
{
    DICT_PROLOG(dr, dls);
    assert(wd);

    Dict_list* cur = dict_find(dls, wd);

    if (cur == NULL)
    {
        dict_add(dr, wd);
    }
    else
    {
        cur->freq++;
    }
}


Dict_list* dict_find(Dict_list* dls, char* wd)
{
    assert(wd);

    Dict_list* cur = dls;
    while (cur)
    {
        if (!strcmp(cur->word, wd))
            break;

        cur = cur->next;
    }

    return cur;
}


void dict_add(Dict* dr, char* wd)
{
    assert(wd);
    assert(dr);
    Dict_list** dls = (Dict_list**) (dr + 1);

    Dict_list* newdls = (Dict_list*) malloc(sizeof(Dict_list));
    assert(newdls);

    int len = strlen(wd);
    char* buf = (char*) malloc(len + 1);
    strcpy(buf, wd);

    newdls->word = buf;
    newdls->freq = 1;
    newdls->next = NULL;

    if (*dls == NULL)
        *dls = newdls;
    else
    {
        Dict_list* cur = *dls;
        while(cur->next)
            cur = cur->next;
        
        cur->next = newdls;
    }
}


void dict_print(Dict* dr)
{
    DICT_PROLOG(dr, dls);
    
    while (dls)
    {
        printf("%d : '%s'\n", dls->freq, dls->word);
        dls = dls->next;
    }
}


void dict_destroy(Dict* dr)
{
    DICT_PROLOG(dr, dls);

    while (dls)
    {
        free(dls->word);
        Dict_list* tmp = dls->next;
        free(dls);
        dls = tmp;
    }
    free(dr);
}

