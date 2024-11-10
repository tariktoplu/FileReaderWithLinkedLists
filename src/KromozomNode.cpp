#include "../include/Kromozom/KromozomNode.hpp"
#include "../include/Gen/GenList.hpp"
KromozomNode::KromozomNode(KromozomNode *next, KromozomNode *prev)
{
    this->genList = new GenList();
    this->next = next;
    this->prev = prev;
}
KromozomNode::~KromozomNode()
{
    delete genList;
}
GenList *KromozomNode::getGeneList() const
{
    return genList;
}