#ifndef _DICT_H_
#define _DICT_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Dict
{
    void (*addword)(struct Dict* dr, const char* wd);
    void (*print)(struct Dict* dr);
    int  (*frequency)(struct Dict* dr, const char* wd);
    int  (*size)(struct Dict* dr);
    void (*destroy)(struct Dict* dr);
} Dict;

Dict* dict();

#ifdef __cplusplus
}
#endif

#endif
