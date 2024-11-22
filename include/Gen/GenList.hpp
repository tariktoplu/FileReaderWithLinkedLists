#ifndef GENLIST_HPP
#define GENLIST_HPP

#include "GenNode.hpp"
#include "../Exceptions/Exception.hpp"
#include "../Kromozom/KromozomList.hpp"

class GenList
{
private:
    GenNode *head;
    int size;

    GenNode *FindPreviousByPosition(int);
    GenList *rgtItr(GenList *, int, GenList *) throw(NoSuchElement); /* 3 fonksiyon taşındı private */
    GenList *lftItr(GenList *, int, GenList *) throw(NoSuchElement);
    GenList *mergeLists(GenList &, GenList &, GenList *) throw(NoSuchElement);

public:
    GenList();
    GenList(const GenList &);
    void Caprazlama(GenList *, GenList *, KromozomList &);

    void yazdir();
    int Count() const;
    bool isEmpty() const;
    void add(const char &);
    void insert(int, const char &) throw(NoSuchElement);
    const char &first() throw(NoSuchElement);
    GenNode *firstNode() const;
    const char &last() throw(NoSuchElement);
    int indexOf(const char &) throw(NoSuchElement);
    void remove(const char &);
    void removeAt(int) throw(NoSuchElement);
    bool find(const char &);
    const char &elementAt(int) throw(NoSuchElement);
    GenNode *FindGenNodeByPosition(int) throw(NoSuchElement);
    void clear();
    friend ostream &operator<<(ostream &, GenList &);
    void printNodesFromPositionInReverseOrder(int) throw(NoSuchElement);
    void printNodes() throw(NoSuchElement);
    void printReverseOrder();
    ~GenList();
};

#endif