#ifndef _DICT_H_
#define _DICT_H_

typedef struct Dict
{
    void (*addword)(struct Dict* dr, const char* wd);
    void (*print)(struct Dict* dr);
    int  (*frequency)(struct Dict* dr, const char* wd);
    int  (*size)(struct Dict* dr);
    void (*destroy)(struct Dict* dr);
} Dict;

Dict* dict();

#endif
