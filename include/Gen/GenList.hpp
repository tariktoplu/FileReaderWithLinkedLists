#ifndef GEN_HPP
#define GEN_HPP

#include "GenNode.hpp"
#include "NoSuchElement.hpp"
#include "../Kromozom/KromozomList.hpp"

class GenList
{
private:
    GenNode *head;
    int size;

    GenNode *FindPreviousByPosition(int index)
    {
        GenNode *prv = head;
        int i = 1;
        for (GenNode *itr = head; i != index; itr = itr->next, i++)
        {
            prv = prv->next;
        }
        return prv;
    }

public:
    void Caprazlama(GenList *list1, GenList *list2)
    {
        }
    GenList()
    {
        head = NULL;
        size = 0;
    }
    int Count() const
    {
        return size;
    }
    bool isEmpty() const
    {
        return size == 0;
    }
    void add(const char &item)
    {
        insert(size, item);
    }
    void insert(int index, const char &item) throw(NoSuchElement)
    {
        if (index < 0 || index > size)
            throw NoSuchElement("No Such Element");
        if (index == 0)
        {
            if (size == 0)
            {
                head = new GenNode(item, head);
                head->next = head->prev = head;
            }
            else
            {
                head = new GenNode(item, head, head->prev);
                head->next->prev = head;
                head->prev->next = head;
            }
        }
        else
        {
            GenNode *prv = FindPreviousByPosition(index);
            prv->next = new GenNode(item, prv->next, prv);
            prv->next->next->prev = prv->next;
        }
        size++;
    }
    const char &first() throw(NoSuchElement)
    {
        if (isEmpty())
            throw NoSuchElement("No Such Element");
        return head->data;
    }
    const char &last() throw(NoSuchElement)
    {
        if (isEmpty())
            throw NoSuchElement("No Such Element");
        return head->prev->data;
    }
    int indexOf(const char &item) throw(NoSuchElement)
    {
        int index = 0;
        for (GenNode *itr = head; index < size; itr = itr->next)
        {
            if (itr->data == item)
                return index;
            index++;
        }
        throw NoSuchElement("No Such Element");
    }
    void remove(const char &item)
    {
        int index = indexOf(item);
        removeAt(index);
    }
    void removeAt(int index) throw(NoSuchElement)
    {
        if (index < 0 || index >= size)
            throw NoSuchElement("No Such Element");
        GenNode *del;
        if (index == 0)
        {
            del = head;
            if (size == 1)
                head = NULL;
            else
            {
                head = head->next;
                head->prev = del->prev;
                del->prev->next = head;
            }
        }
        else
        {
            GenNode *prv = FindPreviousByPosition(index);
            del = prv->next;
            prv->next = del->next;
            del->next->prev = prv;
        }
        size--;
        delete del;
    }
    bool find(const char &item)
    {
        int index = 0;
        for (GenNode *itr = head; index < size; itr = itr->next, index++)
        {
            if (itr->data == item)
                return true;
        }
        return false;
    }
    const char &elementAt(int index) throw(NoSuchElement)
    {
        if (index < 0 || index >= size)
            throw NoSuchElement("No Such Element");
        if (index == 0)
            return head->data;
        return FindPreviousByPosition(index)->next->data;
    }
    void clear()
    {
        while (!isEmpty())
            removeAt(0);
    }
    friend ostream &operator<<(ostream &screen, GenList &rgt)
    {
        int index = 0;
        for (GenNode *itr = rgt.head; index < rgt.size; itr = itr->next, index++)
        {
            screen << itr->data << " <-> ";
        }
        screen << endl;
        return screen;
    }
    void printNodesFromPositionInReverseOrder(int index) throw(NoSuchElement)
    {
        int i = 0;
        if (index < 0 || index >= size)
            throw NoSuchElement("No Such Element");
        for (GenNode *itr = FindPreviousByPosition(index + 1); i < size; itr = itr->prev, i++)
        {
            cout << itr->data << " <-> ";
        }
        cout << endl;
    }
    void printNodesFromPositionInOrder(int index) throw(NoSuchElement)
    {
        int i = 0;
        if (index < 0 || index >= size)
            throw NoSuchElement("No Such Element");
        for (GenNode *itr = FindPreviousByPosition(index + 1); i < size; itr = itr->next, i++)
        {
            cout << itr->data << " <-> ";
        }
        cout << endl;
    }
    void printReverseOrder()
    {
        printNodesFromPositionInReverseOrder(size - 1);
    }
    ~GenList()
    {
        clear();
    }
};

#endif