#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "tree.h"
#include "word.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef struct Tree
{
    void*        data;
    struct Tree* left;
    struct Tree* right;

    int (*cmp)(void* a, void* b);
} Tree;


Tree* tree(void* val, int (*compare)(void* a, void* b));
Tree* tree_find(Tree* root, void* val);
int   tree_size(Tree* root);
void  tree_addElem(Tree* root, void* val);
void  tree_print(Tree* root, void (*printer)(void*));
void  tree_destroy(Tree* root, void (*data_destroy)(void*));

Tree* tree(void* val, int (*compare)(void* a, void* b))
{
    assert(val);

    Tree* tr = (Tree*) malloc(sizeof(Tree));
    assert(tr);

    tr->data = val;
    tr->left = NULL;
    tr->right = NULL;
    tr->cmp = compare;

    return tr;
}


Tree* tree_find(Tree* root, void* val)
{
    assert(root);

    int res = root->cmp(root->data, val);
    
    if (res == 0)
        return root;
    
    if (res > 0 && root->left)
    {
        return tree_find(root->left, val);
    }
    
    if (res < 0 && root->right)
    {
        return tree_find(root->right, val);
    }
        
    return NULL;
}


int tree_size(Tree* root)
{
    if (!root)
        return 0;

    int size = 1;
    
    if (root->left)
        size += tree_size(root->left);

    if (root->right)
        size += tree_size(root->right);

    return size;
}


void tree_addElem(Tree* root, void* val)
{
    assert(root);

    int res = root->cmp(root->data, val);

    if (res > 0)
    {
        if (root->left)
            tree_addElem(root->left, val);
        else
            root->left = tree(val, root->cmp);
    }
    else if (res < 0)
    {
        if (root->right)
            tree_addElem(root->right, val);
        else
            root->right = tree(val, root->cmp);
    }
}


void  tree_print(Tree* root, void (*printer)(void*))
{
    if (root->left)
        tree_print(root->left, printer);

    printer(root->data);

    if (root->right)
        tree_print(root->right, printer);
}


void tree_destroy(Tree* root, void (*data_destroy)(void*))
{
    assert(root);

    if (root->left)
        tree_destroy(root->left, data_destroy);
    
    if (root->right)
        tree_destroy(root->right, data_destroy);
    
    data_destroy(root->data);
    free(root);
}

//////////////////////////////////////////////////////////////////////////

#define TREE_DICT_PROLOG(pdict, newvar)      \
    assert(pdict);                           \
    Tree* newvar = *((Tree**) (pdict + 1));


void tree_dict_addword(Dict* dr, const char* wd);
void tree_dict_print(Dict* dr);
int  tree_dict_frequency(Dict* dr, const char* str);
int  tree_dict_size(Dict* dr);
void tree_dict_destroy(Dict* dr);

static int  compare(void* a, void* b);
static void printer(void* dt);
static void data_destroy(void* dt);


Dict* tree_dict()
{
    Dict* dr = (Dict*) malloc(sizeof(Dict) + sizeof(Tree*));
    assert(dr);

    dr->addword   = tree_dict_addword;
    dr->print     = tree_dict_print;
    dr->frequency = tree_dict_frequency;
    dr->size      = tree_dict_size;
    dr->destroy   = tree_dict_destroy;

    Tree** ptree = (Tree**) (dr + 1);
    *ptree = NULL;

    return dr;
}


void tree_dict_addword(Dict* dr, const char* str)
{
    assert(dr);
    Tree** ptree = (Tree**) (dr + 1);

    Word* wd = word(str);

    if (*ptree == NULL)
    {
        *ptree = tree(wd, compare);
    }
    else
    {
        Tree* tr = *ptree;
        Tree* res = tree_find(tr, wd);

        if (res == NULL)
        {
            tree_addElem(tr, wd);
        }
        else
        {
            Word* wrd = (Word*) res->data;
            wrd->inc(wrd);
            wd->destroy(wd);
        }
    }
}


void tree_dict_print(Dict* dr)
{
    TREE_DICT_PROLOG(dr, tr);
    
    tree_print(tr, printer);
}


int tree_dict_frequency(Dict* dr, const char* str)
{
    TREE_DICT_PROLOG(dr, tr);

    Word* wd = word(str);
    Tree* res = tree_find(tr, wd);
    int fr = 0;

    if (res)
    {
        Word* fnd = (Word*) res->data;
        fr = fnd->frequency(fnd);
    }
    wd->destroy(wd);

    return fr;
}


int tree_dict_size(Dict* dr)
{
    TREE_DICT_PROLOG(dr, tr);

    return tree_size(tr);
}


void tree_dict_destroy(Dict* dr)
{
    TREE_DICT_PROLOG(dr, tr);
    
    tree_destroy(tr, data_destroy);

    free(dr);
}


static int compare(void* a, void* b)
{
    Word* w1 = (Word*) a;
    Word* w2 = (Word*) b;

    return word_cmp(w1, w2);
}


static void printer(void* dt)
{
    Word* wd = (Word*) dt;
    wd->print(wd);
    printf("\n");
}


static void data_destroy(void* dt)
{
    Word* wd = (Word*) dt;
    wd->destroy(wd);   
}

#ifdef __cplusplus
}
#endif
