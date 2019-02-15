#include "reader.h"
#include "dict.h"


int main(int argc, char* argv[])
{
    Reader* rd = reader();
    Dict* dr = dict();

    if (argc != 1)
        rd->init(rd, argv[1]);

    int i = 1;
    do
    {
        char* wd;
        while ((wd = rd->getword(rd)))
            dr->addword(dr, wd);

        i++;
        if (i < argc)
            rd->init(rd, argv[i]);
    } while (i < argc);

    dr->print(dr);

    rd->destroy(rd);
    dr->destroy(dr);

    return 0;
}

