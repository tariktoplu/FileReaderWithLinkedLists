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

    GenNode(const char data, GenNode *next = NULL, GenNode *prev = NULL)
    {
        this->data = data;
        this->next = next;
        this->prev = prev;
    }
};

#endif