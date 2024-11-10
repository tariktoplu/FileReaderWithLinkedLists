#ifndef GEN_HPP
#define GEN_HPP

#include "GenNode.hpp"
#include "../Exceptions/Exception.hpp"
#include "../Kromozom/KromozomList.hpp"

class GenList
{
private:
    GenNode *head;
    int size;

    GenNode *FindPreviousByPosition(int index);

public:
    GenList();
    void Caprazlama(GenList *list1, GenList *list2, KromozomList &kromozomList);
    GenList *rgtItr(GenList *list, int halflength) throw(NoSuchElement);
    GenList *lftItr(GenList *list, int halflength) throw(NoSuchElement);
    GenList *mergeLists(GenList &rgtList, GenList &lftList, GenList *sonListe) throw(NoSuchElement);
    int Count() const;
    bool isEmpty() const;
    void add(const char &item);
    const char &getMiddleElement() throw(NoSuchElement);
    void insert(int index, const char &item) throw(NoSuchElement);
    const char &first() throw(NoSuchElement);
    const char &last() throw(NoSuchElement);
    int indexOf(const char &item) throw(NoSuchElement);
    void remove(const char &item);
    void removeAt(int index) throw(NoSuchElement);
    bool find(const char &item);
    const char &elementAt(int index) throw(NoSuchElement);
    GenNode *FindGenNodeByPosition(int index) throw(NoSuchElement);
    void clear();
    friend ostream &operator<<(ostream &screen, GenList &rgt);
    void printNodesFromPositionInReverseOrder(int index) throw(NoSuchElement);
    void printNodesFromPositionInOrder(int index) throw(NoSuchElement);
    void printReverseOrder();
    ~GenList();
};

#endif