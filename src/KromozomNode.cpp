#include "../include/Kromozom/KromozomNode.hpp"
#include "../include/Gen/GenList.hpp"
KromozomNode::KromozomNode(GenList *genList, KromozomNode *next, KromozomNode *prev)
{
    this->genList = genList; // GenList'i ata
    this->prev = prev;
    this->next = next;
}