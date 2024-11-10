#ifndef GENNODE_HPP
#define GENNODE_HPP
#include <iostream>
using namespace std;

class GenNode
{
public:
    char data;
    GenNode *next;
    GenNode *prev;

    GenNode(const char, GenNode *next = NULL, GenNode *prev = NULL);
};

#endif