#include "../include/Kromozom/KromozomNode.hpp"
#include "../include/Gen/GenList.hpp"
KromozomNode::KromozomNode(KromozomNode *next, KromozomNode *prev)
{
    this->genList = new GenList();
    this->next = next;
    this->prev = prev;
}

GenList *KromozomNode::getGeneList() const
{
    return genList;
}
KromozomNode::~KromozomNode() /* burda hata var çünkü sadece 1 kere çalşıyor yıkıcı bi kaç kere çalışması lazım */

{
    cout << "KromozomNodedaki genlistler siliniyor. Bu 2 defa yazmalı" << endl;
    delete genList;
}