#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#include "reader.h"


enum {BUF_SIZE = 64};

typedef struct Reader_data
{
    FILE* file;
    char* buf;
} Reader_data;

char* reader_getword(Reader* rd);
void  reader_init(Reader* rd, char* filename);
void  reader_destroy(Reader* rd);


Reader* reader()
{
    Reader* newrd = (Reader*) malloc(sizeof(Reader) + sizeof(Reader_data));

    newrd->getword = reader_getword;
    newrd->init    = reader_init;
    newrd->destroy = reader_destroy;

    Reader_data* rdt = (Reader_data*) (newrd + 1);

    rdt->buf = (char*) calloc(BUF_SIZE, sizeof(char));
    rdt->file = stdin;

    return newrd;
}


void reader_init(Reader* rd, char* filename)
{
    assert(rd);
    Reader_data* rdt = (Reader_data*) (rd + 1);

    if (rdt->file != stdin)
        fclose(rdt->file);

    rdt->file = fopen(filename, "r");
    if (!rdt->file)
    {
        fprintf(stderr, "file '%s' error: %s\n",
                filename, strerror(errno));
    }
}


char* reader_getword(Reader* rd)
{
    assert(rd);
    Reader_data* rdt = (Reader_data*) (rd + 1);

    if (rdt->file == NULL)
        return NULL;

    int c = EOF, i = 0;
    while ((c = fgetc(rdt->file)) != EOF && !isalpha(c));
    if (c == EOF)
        return NULL;

    while (isalpha(c) && i < BUF_SIZE - 1)
    {
        rdt->buf[i] = (char) c;
        c = fgetc(rdt->file);
        i++;
    }
    rdt->buf[i] = '\0';
    
    return rdt->buf;
} 


void reader_destroy(Reader* rd)
{
    assert(rd);
    Reader_data* rdt = (Reader_data*) (rd + 1);
 
    if (rdt->file != stdin && rdt->file != NULL)
        fclose(rdt->file);

    free(rdt->buf);
    free(rd);
}

