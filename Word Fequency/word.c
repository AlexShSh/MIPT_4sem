#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "word.h"

#define WORD_PROLOG(pword, newvar)               \
    assert(pword);                               \
    Word_data* newvar = (Word_data*) (pword + 1);


typedef struct Word_data
{
    char* data;
    int   freq;
} Word_data;

int  word_isequal(Word* wd, const char* str);
int  word_frequency(Word* wd);
void word_inc(Word* wd);
void word_print(Word* wd);
void word_destroy(Word* wd);


Word* word(const char* str)
{
    Word* wd = (Word*) malloc(sizeof(Word) + sizeof(Word_data));
    WORD_PROLOG(wd, wdt);

    wd->isequal   = word_isequal;
    wd->frequency = word_frequency;
    wd->inc       = word_inc;
    wd->print     = word_print;
    wd->destroy   = word_destroy;

    size_t len = strlen(str);
    wdt->data = (char*) malloc(len + 1);
    strcpy(wdt->data, str);
    wdt->freq = 1;

    return wd;
}


int word_cmp(Word* a, Word* b)
{
    WORD_PROLOG(a, w1);
    WORD_PROLOG(b, w2);
    
    return strcmp(w1->data, w2->data);
}


int word_frequency(Word* wd)
{
    WORD_PROLOG(wd, wdt);

    return wdt->freq;
}


int  word_isequal(Word* wd, const char* str)
{
    assert(str);
    WORD_PROLOG(wd, wdt);

    return !strcmp(wdt->data, str);
}


void word_inc(Word* wd)
{
    WORD_PROLOG(wd, wdt);
    
    wdt->freq++;
}


void word_print(Word* wd)
{
    WORD_PROLOG(wd, wdt);

    printf("%2d - '%s'", wdt->freq, wdt->data);
}


void word_destroy(Word* wd)
{
    WORD_PROLOG(wd, wdt);

    free(wdt->data);
    free(wd);
}
