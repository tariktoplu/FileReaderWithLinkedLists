#include "../include/Kromozom/KromozomNode.hpp"
#include "../include/Gen/GenList.hpp"
KromozomNode::KromozomNode(GenList *genList, KromozomNode *next, KromozomNode *prev)
{
    this->genList = genList;
    this->next = next;
    this->prev = prev;
}

GenList *KromozomNode::getGeneList() const
{
    return genList;
}