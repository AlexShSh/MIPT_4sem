#ifndef _WORD_H_
#define _WORD_H_

typedef struct Word
{
    int  (*isequal)(struct Word* wd, char* str);
    void (*inc)(struct Word* wd);
    void (*print)(struct Word* wd);
    void (*destroy)(struct Word* wd);
} Word;

Word* word(char* str);
int   word_cmp(Word* a, Word* b);

#endif
