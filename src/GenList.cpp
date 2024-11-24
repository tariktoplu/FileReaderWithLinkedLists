#include "../include/Gen/GenList.hpp"

GenNode *GenList::FindPreviousByPosition(int index)
{
    GenNode *prv = head;
    int i = 1;
    for (GenNode *itr = head; i != index; itr = itr->next, i++)
    {
        prv = prv->next;
    }
    return prv;
}
GenList::GenList()
{
    head = NULL;
    size = 0;
} // Caprazlama fonksiyonu bitti sanırım

GenList::GenList(const GenList &copyItem)
{
    head = nullptr;
    size = 0;

    // Diğer listenin boş olup olmadığını kontrol et
    if (copyItem.isEmpty())
    {
        return;
    }

    // İlk düğümü kopyala
    GenNode *otherCurrent = copyItem.head;
    for (int i = 0; i < copyItem.size; i++)
    {
        add(otherCurrent->data);
        otherCurrent = otherCurrent->next;
    }
}

void GenList::yazdir()
{
    if (isEmpty())
    {
        cout << "Liste boş." << endl;
        return;
    }

    char firstElement = first()->data; // İlk elemanı al
    bool foundSmaller = false;

    for (GenNode *itr = head->prev; itr != head; itr = itr->prev)
    {
        if (itr->data < firstElement)
        {
            cout << itr->data << " ";
            foundSmaller = true;
            break;
        }
    }

    if (!foundSmaller)
    {
        cout << firstElement << " "; // İlk elemanı yazdır
    }
}

int GenList::Count() const
{
    return size;
}
bool GenList::isEmpty() const
{
    return size == 0;
}
void GenList::add(const char &item)
{
    insert(size, item);
}
void GenList::insert(int index, const char &item) throw(NoSuchElement)
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
GenNode *GenList::first() const
{
    return head;
}
const char &GenList::last() throw(NoSuchElement)
{
    if (isEmpty())
        throw NoSuchElement("No Such Element");
    return head->prev->data;
}
int GenList::indexOf(const char &item) throw(NoSuchElement)
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
void GenList::remove(const char &item)
{
    int index = indexOf(item);
    removeAt(index);
}
void GenList::removeAt(int index) throw(NoSuchElement)
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
bool GenList::find(const char &item)
{
    int index = 0;
    for (GenNode *itr = head; index < size; itr = itr->next, index++)
    {
        if (itr->data == item)
            return true;
    }
    return false;
}
const char &GenList::elementAt(int index) throw(NoSuchElement)
{
    if (index < 0 || index >= size)
        throw NoSuchElement("No Such Element");
    if (index == 0)
        return head->data;
    return FindPreviousByPosition(index)->next->data;
}

GenNode *GenList::FindGenNodeByPosition(int index) throw(NoSuchElement)
{
    if (index < 0 || index >= size)
        throw NoSuchElement("No Such Element");

    GenNode *itr;

    // Eğer index ortadan küçükse baştan, büyükse sondan başla
    if (index < size / 2)
    {
        itr = head;
        for (int i = 0; i < index; ++i)
        {
            itr = itr->next;
        }
    }
    else
    {
        itr = head->prev; // Sondan başla
        for (int i = size - 1; i > index; --i)
        {
            itr = itr->prev;
        }
    }
    return itr;
}
void GenList::clear()
{
    while (!isEmpty())
        removeAt(0);
}
ostream &operator<<(ostream &screen, GenList &rgt)
{
    int index = 0;
    for (GenNode *itr = rgt.head; index < rgt.size; itr = itr->next, index++)
    {
        screen << itr->data << " <-> ";
    }
    screen << endl;
    return screen;
}
GenList::~GenList()
{
    clear();
}
