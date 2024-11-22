#include "../include/Gen/GenNode.hpp"

GenNode::GenNode(const char data, GenNode *next, GenNode *prev)
{
    this->data = data;
    this->next = next;
    this->prev = prev;
}
