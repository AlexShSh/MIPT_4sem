#ifndef _READER_H_
#define _READER_H_

typedef struct Reader
{
    char* (*getword)(struct Reader* rd);
    void  (*init)(struct Reader* rd, char* filename);
    void  (*destroy)(struct Reader* rd);
} Reader;

Reader* reader();

#endif
