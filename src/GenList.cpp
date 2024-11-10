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
void GenList::Caprazlama(GenList *list1, GenList *list2, KromozomList &kromozomList)
{
    int orta1 = list1->Count() / 2;
    int orta2 = list2->Count() / 2;

    GenList *sonListe1 = new GenList();

    GenList *yeniGenList1;
    GenList *yeniGenList2;

    lftItr(list1, orta1, yeniGenList1);
    rgtItr(list2, orta2, yeniGenList1); // list 2 nin Sağ yarıyı al

    rgtItr(list1, orta1, yeniGenList2); // Sol yarıyı al
    lftItr(list2, orta2, yeniGenList2);

    mergeLists(*yeniGenList1, *yeniGenList2, sonListe1);

    GenList *sonListe2 = new GenList();

    // sonListe1 ve sonListe2'yi kromozomList'e ekle
    kromozomList.add(sonListe1);
    kromozomList.add(sonListe2);

    sonListe1->printNodes();
    sonListe2->printNodes();

    // Bellek sızıntısını önlemek için geçici listeleri sil
    delete yeniGenList1;
    delete yeniGenList2;
}

// Sağ iteratörü: Sağ yarıyı almak için
GenList *GenList::rgtItr(GenList *list, int halflength, GenList *yeniList) throw(NoSuchElement)
{                                                                /* yukarıda oluşturduğum gecici listeyi passleyebilirim */
    GenNode *itr = list->FindPreviousByPosition(halflength + 1); // Orta noktadan sonra başlayan iteratör

    for (int i = 0; i < halflength; ++i)
    {
        yeniList->add(itr->data); // Mevcut düğümün verisini ekle
        itr = itr->next;          // Sağa ilerle
    }

    return yeniList;
    /* bu çöp olarak kaldı olmaz !!!!!!!!!! */
}

// Sol iteratörü: Sol yarıyı almak için
GenList *GenList::lftItr(GenList *list, int halflength, GenList *yeniList) throw(NoSuchElement)
{

    GenNode *itr = list->FindPreviousByPosition(halflength); // Orta noktaya kadar ilerleyen iteratör

    for (int i = 0; i < halflength; ++i)
    {
        yeniList->add(itr->data); // Mevcut düğümün verisini ekle
        itr = itr->prev;          // Sola ilerle
    }
    return yeniList;
}

// Listeleri birleştiren fonksiyon
GenList *GenList::mergeLists(GenList &rgtList, GenList &lftList, GenList *sonListe) throw(NoSuchElement)
{
    // Eğer her iki liste de boş değilse
    if (!rgtList.isEmpty() && !lftList.isEmpty())
    {
        // Sağ listenin başını son listeye ekle
        sonListe->head = rgtList.head;

        // Sağ listenin sonunu (prev) sol listenin başına bağla
        rgtList.head->prev = lftList.head->prev; // Sağ listenin sonunu sol listenin sonuna bağla
        lftList.head->prev->next = rgtList.head; // Sol listenin sonunu sağ listenin başına bağla

        // Sol listenin başını son listeye ekle
        lftList.head->prev = rgtList.head->prev; // Sol listenin sonunu sağ listenin sonuna bağla
        rgtList.head->prev->next = lftList.head; // Sağ listenin sonunu sol listenin başına bağla
    }
    else if (!rgtList.isEmpty()) // Eğer sadece sağ liste doluysa
    {
        sonListe->head = rgtList.head;
        rgtList.head->prev = rgtList.head; // Sağ listenin sonunu kendisine bağla
    }
    else if (!lftList.isEmpty()) // Eğer sadece sol liste doluysa
    {
        sonListe->head = lftList.head;
        lftList.head->prev = lftList.head; // Sol listenin sonunu kendisine bağla
    }
    else // Her iki liste de boşsa
    {
        sonListe->head = NULL; // Son liste de boş
    }

    // Döngüsel bağlantı kurma (Circular Doubly Linked List)
    if (sonListe->head != NULL)
    {
        GenNode *firstNode = sonListe->head;
        GenNode *lastNode = firstNode->prev; // İlk düğümün öncesi son düğüm
        firstNode->prev = lastNode;          // İlk düğümün öncesini son düğüm yap
        lastNode->next = firstNode;          // Son düğümün sonrasını ilk düğüm yap
    }

    // Birleştirilen listeyi döndür
    return sonListe;
}

void GenList::yazdir()
{
    if (isEmpty())
    {
        cout << "Liste boş." << endl;
        return;
    }

    char firstElement = first(); // İlk elemanı al
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
void GenList::printNodes() throw(NoSuchElement)
{
    int index = 0;
    int i = 0;
    for (GenNode *itr = FindPreviousByPosition(index + 1); i < size; itr = itr->next, i++)
    {
        cout << itr->data << " ";
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
