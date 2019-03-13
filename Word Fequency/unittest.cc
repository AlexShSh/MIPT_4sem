#include <limits.h>

#include "dict.h"
#include "tree.h"
#include "gtest/gtest.h"

namespace{

TEST(DictTest, Empty)
{
    Dict* dr =  dict();

    EXPECT_EQ(dr->size(dr), 0);
    EXPECT_EQ(dr->frequency(dr, "alex"), 0);

    dr->destroy(dr);
}

TEST(DictTest, OneElem)
{
    Dict* dr = dict();
    dr->addword(dr, "alex");

    EXPECT_EQ(dr->size(dr), 1);
    EXPECT_EQ(dr->frequency(dr, "alex"), 1);

    dr->addword(dr, "alex");

    EXPECT_EQ(dr->frequency(dr, "alex"), 2);
    EXPECT_EQ(dr->frequency(dr, "alexx"), 0);
    EXPECT_EQ(dr->size(dr), 1);

    dr->destroy(dr);
}

TEST(DictTest, Elems)
{
    Dict* dr = dict();
    dr->addword(dr, "alex");
    dr->addword(dr, "alex");
    dr->addword(dr, "alex");
    dr->addword(dr, "ALEX");
    dr->addword(dr, "Roma");
    dr->addword(dr, "Roma");
    dr->addword(dr, "Romchik");
    dr->addword(dr, "R");

    EXPECT_EQ(dr->size(dr), 5);
    EXPECT_EQ(dr->frequency(dr, "alex"), 3);
    EXPECT_EQ(dr->frequency(dr, "Roma"), 2);
    EXPECT_EQ(dr->frequency(dr, "ALEX"), 1);
    EXPECT_EQ(dr->frequency(dr, "AlEx"), 0);

    dr->destroy(dr);
}

TEST(DictTreeTest, Empty)
{
    Dict* dr = tree_dict();

    EXPECT_EQ(dr->size(dr), 0);
    EXPECT_EQ(dr->frequency(dr, "alex"), 0);

    dr->destroy(dr);
}

TEST(DictTreeTest, OneElem)
{
    Dict* dr = tree_dict();
    dr->addword(dr, "alex");

    EXPECT_EQ(dr->size(dr), 1);
    EXPECT_EQ(dr->frequency(dr, "alex"), 1);

    dr->addword(dr, "alex");

    EXPECT_EQ(dr->frequency(dr, "alex"), 2);
    EXPECT_EQ(dr->frequency(dr, "alexx"), 0);
    EXPECT_EQ(dr->size(dr), 1);

    dr->destroy(dr);
}

TEST(DictTreeTest, Elems)
{
    Dict* dr = tree_dict();
    dr->addword(dr, "alex");
    dr->addword(dr, "alex");
    dr->addword(dr, "alex");
    dr->addword(dr, "ALEX");
    dr->addword(dr, "Roma");
    dr->addword(dr, "Roma");
    dr->addword(dr, "Romchik");
    dr->addword(dr, "R");

    EXPECT_EQ(dr->size(dr), 5);
    EXPECT_EQ(dr->frequency(dr, "alex"), 3);
    EXPECT_EQ(dr->frequency(dr, "Roma"), 2);
    EXPECT_EQ(dr->frequency(dr, "ALEX"), 1);
    EXPECT_EQ(dr->frequency(dr, "AlEx"), 0);

    dr->destroy(dr);
}
}
