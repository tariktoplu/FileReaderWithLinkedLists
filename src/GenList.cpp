#include "../Gen/GenList.hpp"

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
void GenList::Caprazlama(GenList *list1, GenList *list2, KromozomList &kromozomList)
{
    int orta1 = list1->Count() / 2;
    int orta2 = list2->Count() / 2;

    GenList *yeniGenList1 = rgtItr(list2, orta2); // Sağ yarıyı al
    GenList *yeniGenList2 = lftItr(list1, orta1); // Sol yarıyı al

    GenList *sonListe1 = new GenList();
    mergeLists(*yeniGenList1, *yeniGenList2, sonListe1);

    GenList *yeniGenList3 = rgtItr(list1, orta1);
    GenList *yeniGenList4 = lftItr(list2, orta2);

    GenList *sonListe2 = new GenList();
    mergeLists(*yeniGenList3, *yeniGenList4, sonListe2);

    // sonListe1 ve sonListe2'yi kromozomList'e ekle
    kromozomList.add(sonListe1);
    kromozomList.add(sonListe2);

    // Bellek sızıntısını önlemek için geçici listeleri sil
    delete yeniGenList1;
    delete yeniGenList2;
    delete yeniGenList3;
    delete yeniGenList4;
}

// Sağ iteratörü: Sağ yarıyı almak için
GenList *GenList::rgtItr(GenList *list, int halflength) throw(NoSuchElement)
{ /* yukarıda oluşturduğum gecici listeyi passleyebilirim */
    GenList *yeniListeRgt = new GenList();
    GenNode *itr = FindPreviousByPosition(halflength + 1); // Orta noktadan sonra başlayan iteratör

    for (int i = 0; i < halflength; ++i)
    {
        yeniListeRgt->add(itr->data); // Mevcut düğümün verisini ekle
        itr = itr->next;              // Sağa ilerle
    }

    return yeniListeRgt;
    /* bu çöp olarak kaldı olmaz !!!!!!!!!! */
}

// Sol iteratörü: Sol yarıyı almak için
GenList *GenList::lftItr(GenList *list, int halflength) throw(NoSuchElement)
{
    GenList *yeniListeLft = new GenList();
    GenNode *itr = FindPreviousByPosition(halflength); // Orta noktaya kadar ilerleyen iteratör

    for (int i = 0; i < halflength; ++i)
    {
        yeniListeLft->add(itr->data); // Mevcut düğümün verisini ekle
        itr = itr->prev;              // Sola ilerle
    }
    /* bu çöp olarak kaldı olmaz !!!!!!!!!! */
    return yeniListeLft;
}

// Listeleri birleştiren fonksiyon
GenList *GenList::mergeLists(GenList &rgtList, GenList &lftList, GenList *sonListe) throw(NoSuchElement)
{
    // Sağ listeyi yeni listeye ekle
    for (int i = 0; i < rgtList.Count(); i++)
    {
        sonListe->add(rgtList.elementAt(i)); // Sağ yarıyı ekle
    }

    // Sol listeyi yeni listeye ekle
    for (int i = 0; i < lftList.Count(); i++)
    {
        sonListe->add(lftList.elementAt(i)); // Sol yarıyı ekle
    }

    // Döngüsel bağlantı kurma (Circular Doubly Linked List)
    if (sonListe->Count() > 1)
    {
        GenNode *firstNode = sonListe->head;
        GenNode *lastNode = sonListe->head->prev;
        firstNode->prev = lastNode;
        lastNode->next = firstNode;
    }

    return sonListe;
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
const char &GenList::getMiddleElement() throw(NoSuchElement) /* kaldırılabilir bence */
{
    if (isEmpty() || size % 2 == 0)
        throw NoSuchElement("No middle element - list is empty or size is even.");

    int middleIndex = size / 2;
    return elementAt(middleIndex);
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
const char &GenList::first() throw(NoSuchElement)
{
    if (isEmpty())
        throw NoSuchElement("No Such Element");
    return head->data;
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
void GenList::printNodesFromPositionInReverseOrder(int index) throw(NoSuchElement)
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
void GenList::printNodesFromPositionInOrder(int index) throw(NoSuchElement)
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
void GenList::printReverseOrder()
{
    printNodesFromPositionInReverseOrder(size - 1);
}
GenList::~GenList()
{
    clear();
}
