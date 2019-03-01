#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "tree.h"
#include "word.h"


typedef struct Tree
{
    void*        data;
    struct Tree* left;
    struct Tree* right;

    int (*cmp)(void* a, void* b);
} Tree;


Tree* tree(void* val, int (*compare)(void* a, void* b));
Tree* tree_find(Tree* root, void* val);
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


void tree_dict_addword(Dict* dr, char* wd);
void tree_dict_print(Dict* dr);
void tree_dict_destroy(Dict* dr);

int  compare(void* a, void* b);
void printer(void* dt);
void data_destroy(void* dt);


Dict* tree_dict()
{
    Dict* dr = (Dict*) malloc(sizeof(Dict) + sizeof(Tree*));
    assert(dr);

    dr->addword = tree_dict_addword;
    dr->print   = tree_dict_print;
    dr->destroy = tree_dict_destroy;

    Tree** ptree = (Tree**) (dr + 1);
    *ptree = NULL;

    return dr;
}


void tree_dict_addword(Dict* dr, char* str)
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


void tree_dict_destroy(Dict* dr)
{
    TREE_DICT_PROLOG(dr, tr);
    
    tree_destroy(tr, data_destroy);

    free(dr);
}


int compare(void* a, void* b)
{
    Word* w1 = (Word*) a;
    Word* w2 = (Word*) b;

    return word_cmp(w1, w2);
}


void printer(void* dt)
{
    Word* wd = (Word*) dt;
    wd->print(wd);
    printf("\n");
}


void data_destroy(void* dt)
{
    Word* wd = (Word*) dt;
    wd->destroy(wd);   
}

