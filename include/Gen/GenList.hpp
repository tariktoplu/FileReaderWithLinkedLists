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

public:
    GenList();
    GenList(const GenList &);
    void yazdir();
    int Count() const;
    bool isEmpty() const;
    void add(const char &);
    void insert(int, const char &) throw(NoSuchElement);
    GenNode *first() const;
    const char &last() throw(NoSuchElement);
    int indexOf(const char &) throw(NoSuchElement);
    void remove(const char &);
    void removeAt(int) throw(NoSuchElement);
    bool find(const char &);
    const char &elementAt(int) throw(NoSuchElement);
    GenNode *FindGenNodeByPosition(int) throw(NoSuchElement);
    void clear();
    friend ostream &operator<<(ostream &, GenList &);
    ~GenList();
};

#endif