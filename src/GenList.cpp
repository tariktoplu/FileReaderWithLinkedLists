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
}
GenList::GenList(const GenList &diger)
{
    head = NULL; /* burada kaldın */
    size = 0;

    if (diger.size > 0)
    {
        GenNode *itr = diger.head;
        for (int i = 0; i < diger.size; i++)
        {
            add(itr->data);
            itr = itr->next;
        }
        head->prev = itr->prev; // Son elemanın prev'ini başa bağla
        itr->prev->next = head;
    }

} /*  // Caprazlama fonksiyonu bitti sanırım
 void GenList::Caprazlama(GenList *list1, GenList *list2, KromozomList &kromozomList)
 {
     int orta1 = list1->Count() / 2;
     int orta2 = list2->Count() / 2;
     // Yeni GenList nesnelerini oluştur
     GenList *yeniGenList1 = new GenList();
     GenList *yeniGenList2 = new GenList();
     // Listelerin yarılarını al
     lftItr(list1, orta1, yeniGenList1); // List 1'in sol yarısını al
     rgtItr(list2, orta2, yeniGenList1); // List 2'nin sağ yarısını al

     rgtItr(list1, orta1, yeniGenList2); // List 1'in sağ yarısını al
     lftItr(list2, orta2, yeniGenList2); // List 2'nin sol yarısını al

     // İki yeni listeyi birleştir
     GenList *sonListe1 = new GenList();
     mergeLists(*yeniGenList1, *yeniGenList2, sonListe1);

     GenList *sonListe2 = new GenList();
     mergeLists(*yeniGenList1, *yeniGenList2, sonListe2);

     // Sonuçları kromozomList'e ekle
     kromozomList.add(sonListe1);
     kromozomList.add(sonListe2);

     // Sonuçları yazdır
     cout << "yazdırma ya çalışmıyor ya da birleştirmelerde sıkıntı var";

     sonListe1->printNodes();
     sonListe2->printNodes();

     cout << "\n ekrana yazdırıldı yeniler";

     // Bellek sızıntısını önlemek için geçici listeleri sil
     delete yeniGenList1;
     delete yeniGenList2;
 }*/
/*  bu çaprazlamaya gerek yok sanırım

// Sağ iteratörü: Sağ yarıyı almak için
GenList *GenList::rgtItr(GenList *list, int halflength, GenList *yeniList) throw(NoSuchElement)
{
GenNode *itr = list->FindPreviousByPosition(halflength + 1); // Orta noktadan sonra başlayan iteratör

for (int i = 0; i < halflength; ++i)
{
    yeniList->add(itr->data); // Mevcut düğümün verisini ekle
    itr = itr->next;          // Sağa ilerle
}

return yeniList;
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

if (!foundSmaller)
{
    cout << firstElement << " "; // İlk elemanı yazdır
}
} */

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

/* silincek hiç kullanılmamış
const char &GenList::last() throw(NoSuchElement)
{
   if (isEmpty())
       throw NoSuchElement("No Such Element");
   return head->prev->data;
} */
GenNode *GenList::firstNode() const
{
    return head;
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
} /* hiç kullanılmamış
 bool GenList::find(const char &item)
 {
     int index = 0;
     for (GenNode *itr = head; index < size; itr = itr->next, index++)
     {
         if (itr->data == item)
             return true;
     }
     return false;
 } */
/*
const char &GenList::elementAt(int index) throw(NoSuchElement)
{
if (index < 0 || index >= size)
   throw NoSuchElement("No Such Element");
if (index == 0)
   return head->data;
return FindPreviousByPosition(index)->next->data;
} bu da kullanılmamış */

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
    {
        removeAt(0);
        cout << "GenList sınıfındaki yıkıcı calıstı tek tek siliniyor";
    }
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
