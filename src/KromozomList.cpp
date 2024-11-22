
/* caprazlama düzenlenecek */
#include "../include/Kromozom/KromozomList.hpp"
#include "../include/Gen/GenList.hpp"

KromozomList::KromozomList() : head(nullptr),
                               quarterNode(nullptr), midNode(nullptr),
                               threeQuarterNode(nullptr), size(0)
{
    updateReferencePoints();
}

void KromozomList::processCommands(KromozomList &kromozomlar)
{
    ifstream islemlerFile("Islemler.txt");

    if (!islemlerFile.is_open())
    {
        cout << "Islemler.txt dosyası açılamadı!" << endl;
        return;
    }

    string line;
    while (getline(islemlerFile, line))
    {
        istringstream iss(line);
        char command;
        int index1, index2;

        // Komut karakterini oku
        if (!(iss >> command))
        {
            continue; // Eğer komut okunamazsa, bu satırı atla
        }

        // Komut karakterine göre işlemleri yap
        if (command == 'C' || command == 'c')
        {
            // Çaprazlama komutu
            if (iss >> index1 >> index2)
            {
                try
                {
                    kromozomlar.Caprazlama(index1, index2); // Caprazlama fonksiyonunu çağır
                }
                catch (const char *e)
                {
                    cout << "Hata: " << e << endl;
                }
            }
            else
            {
                cout << "Geçersiz C komutu: " << line << endl;
            }
        }
        else if (command == 'M' || command == 'm')
        {
            // Mutasyon komutu
            if (iss >> index1 >> index2)
            {
                try
                {
                    kromozomlar.Mutasyon(index1, index2); // Mutasyon fonksiyonunu çağır
                }
                catch (const char *e)
                {
                    cout << "Hata: " << e << endl;
                }
            }
            else
            {
                cout << "Geçersiz M komutu: " << line << endl;
            }
        }
        else
        {
            cout << "Geçersiz komut: " << command << endl;
        }
    }

    islemlerFile.close();
    cout << "İşlemler tamamlandı." << endl; // Dosyayı kapat
}

void KromozomList::updateReferencePoints()
{
    if (size < 4)
    {
        quarterNode = midNode = threeQuarterNode = head;
        return;
    }

    quarterIndex = size / 4;
    midIndex = size / 2;
    threeQuarterIndex = 3 * size / 4;

    KromozomNode *current = head;
    int currentIndex = 0;

    // Quarter node'u bul
    while (currentIndex < quarterIndex)
    {
        current = current->next;
        currentIndex++;
    }
    quarterNode = current;

    // Mid node'u bul
    while (currentIndex < midIndex)
    {
        current = current->next;
        currentIndex++;
    }
    midNode = current;

    // ThreeQuarter node'u bul
    while (currentIndex < threeQuarterIndex)
    {
        current = current->next;
        currentIndex++;
    }
    threeQuarterNode = current;
}

KromozomNode *KromozomList::FindPreviousByPosition(int index)
{
    KromozomNode *prv = head;
    int i = 1;
    for (KromozomNode *itr = head; i != index; itr = itr->next, i++)
    {
        prv = prv->next;
    }
    return prv;
}

void KromozomList::yazdir()
{
    KromozomNode *current = head;
    for (int i = 0; i < size; i++)
    {
        GenList *genList = current->genList;
        genList->yazdir(); // GenList'in yazdırma fonksiyonunu çağır
        current = current->next;
    }
    cout << endl;
}
void KromozomList::Caprazlama(int index1, int index2)
{
    if (index1 < 0 || index1 >= size || index2 < 0 || index2 >= size)
    {
        throw NoSuchElement("Invalid index for crossover.");
    }
    /*
        // Kromozomları bul
        KromozomNode *kromozom1 = FindFromNodeByPosition(index1);
        KromozomNode *kromozom2 = FindFromNodeByPosition(index2);

        if (kromozom1 == nullptr || kromozom2 == nullptr)
        {
            throw NoSuchElement("Kromozom not found.");
        } */

    KromozomNode *kromozom1 = head;
    KromozomNode *kromozom2 = head;

    for (int i = 0; i < index1; i++)
        kromozom1 = kromozom1->next;
    for (int i = 0; i < index2; i++)
        kromozom2 = kromozom2->next;
    // Yeni gen listelerini oluştur
    GenList *caprazlananGenList1 = new GenList();
    GenList *caprazlananGenList2 = new GenList();

    // Orta noktaları hesapla
    int orta1 = kromozom1->genList->Count() / 2;
    int orta2 = kromozom2->genList->Count() / 2;

    GenNode *itr = kromozom1->genList->firstNode();
    for (int i = 0; i < orta1; i++)
    {
        caprazlananGenList1->add(itr->data);
        itr = itr->next;
    }

    itr = kromozom2->genList->firstNode();
    for (int i = 0; i < orta2; i++)
        itr = itr->next;
    for (int i = orta2; i < kromozom2->genList->Count(); i++)
    {
        caprazlananGenList1->add(itr->data);
        itr = itr->next;
    }

    itr = kromozom2->genList->firstNode();
    for (int i = 0; i < orta2; i++)
    {
        caprazlananGenList2->add(itr->data);
        itr = itr->next;
    }

    itr = kromozom1->genList->firstNode();
    for (int i = 0; i < orta1; i++)
        itr = itr->next;
    for (int i = orta1; i < kromozom1->genList->Count(); i++)
    {
        caprazlananGenList2->add(itr->data);
        itr = itr->next;
    }

    this->add(*caprazlananGenList1);
    this->add(*caprazlananGenList2);

    delete caprazlananGenList1;
    delete caprazlananGenList2;
}
/* bu çaprazlama bitti gibi
void KromozomList::Caprazlama(int index1, int index2)
{
    if (index1 < 0 || index1 >= size || index2 < 0 || index2 >= size)
    {
        throw NoSuchElement("Invalid index for crossover.");
    }

    KromozomNode *kromozom1 = FindFromNodeByPosition(index1);
    KromozomNode *kromozom2 = FindFromNodeByPosition(index2);

    if (kromozom1 == nullptr || kromozom2 == nullptr)
    {
        throw NoSuchElement("Kromozom not found.");
    }

    GenList *genList1 = kromozom1->genList;
    GenList *genList2 = kromozom2->genList;

    // İlk kromozomun orta noktası
    int mid1 = genList1->Count() / 2;
    // İkinci kromozomun orta noktası
    int mid2 = genList2->Count() / 2;

    // Yeni kromozomları oluştur
    GenList *newGenList1 = new GenList();
    GenList *newGenList2 = new GenList();

    // Kromozom 1'in sol tarafı ve Kromozom 2'nin sağ tarafı
    for (int i = 0; i < mid1; i++)
    {
        GenNode *node = genList1->FindGenNodeByPosition(i); // Kromozom 1'in baştan mid1'e kadar olan genleri
        newGenList1->add(node->data);                       // Yeni gen listesine ekle
    }
    for (int i = mid2; i < genList2->Count(); i++)
    {
        GenNode *node = genList2->FindGenNodeByPosition(i); // Kromozom 2'nin mid2'den sona kadar olan genleri
        newGenList1->add(node->data);                       // Yeni gen listesine ekle
    }

    // Kromozom 1'in sağ tarafı ve Kromozom 2'nin sol tarafı
    for (int i = mid1; i < genList1->Count(); i++)
    {
        GenNode *node = genList1->FindGenNodeByPosition(i); // Kromozom 1'in mid1'den sona kadar olan genleri
        newGenList2->add(node->data);                       // Yeni gen listesine ekle
    }
    for (int i = 0; i < mid2; i++)
    {
        GenNode *node = genList2->FindGenNodeByPosition(i); // Kromozom 2'nin baştan mid2'ye kadar olan genleri
        newGenList2->add(node->data);                       // Yeni gen listesine ekle
    }

    // Yeni kromozomları popülasyona ekle
    add(*newGenList1);
    add(*newGenList2);
    newGenList1->printNodes();
    newGenList2->printNodes();
} */

/* void Mutasyon(int index, int column)
{
    if (index < 0 || column >= size)
    {
        throw NoSuchElement("Invalid kromozom index for mutation.");
    }
    KromozomNode *kromozomNode = FindPreviousByPosition(index);
    GenList *genList = kromozomNode->genList; /* gen listesini çekti pointera  */

/* if (column < 0 || column >= genList->Count())
{
    throw NoSuchElement("Invalid gen index for mutation.");
}

GenNode *genNode = genList->FindNodeByPosition(index);
genNode->data = 'X';
 */

/* mutasyon blackboxtan duzenlenecek */
void KromozomList::Mutasyon(int index, int column)
{
    if (index < 0 || index >= size)
    {
        throw NoSuchElement("Invalid kromozom index for mutation.");
    }

    // Kromozom düğümünü bul
    KromozomNode *kromozomNode = FindFromNodeByPosition(index);
    GenList *genList = kromozomNode->genList;

    if (column < 0 || column >= genList->Count())
    {
        throw NoSuchElement("Invalid gen index for mutation.");
    }

    // Gen düğümünü bul ve mutasyon yap
    GenNode *genNode = genList->FindGenNodeByPosition(column); // column parametresi ile genNode'u buluyoruz
    genNode->data = 'X';                                       // Geni mutasyona uğrat (örneğin, verisini 'X' olarak değiştir)

    // Geni değiştirdikten sonra, gen listesini yazdır
    genList->printNodes();
}
KromozomNode *KromozomList::FindFromNodeByPosition(int index)
{
    if (index < 0 || index >= size)
        throw NoSuchElement("No Such Element");

    KromozomNode *start;
    int steps;

    // En yakın referans noktasından başla
    if (index <= quarterIndex)
    {
        if (index <= quarterIndex / 2)
        {
            start = head;
            steps = index;
        }
        else
        {
            start = quarterNode;
            steps = index - quarterIndex;
        }
    }
    else if (index <= midIndex)
    {
        if (index - quarterIndex <= (midIndex - quarterIndex) / 2)
        {
            start = quarterNode;
            steps = index - quarterIndex;
        }
        else
        {
            start = midNode;
            steps = index - midIndex;
        }
    }
    else if (index <= threeQuarterIndex)
    {
        if (index - midIndex <= (threeQuarterIndex - midIndex) / 2)
        {
            start = midNode;
            steps = index - midIndex;
        }
        else
        {
            start = threeQuarterNode;
            steps = index - threeQuarterIndex;
        }
    }
    else
    {
        if (index - threeQuarterIndex <= (size - threeQuarterIndex) / 2)
        {
            start = threeQuarterNode;
            steps = index - threeQuarterIndex;
        }
        else
        {
            start = head->prev; /* buradaki taili head->prev olarak değiştirdim*/
            steps = size - 1 - index;
        }
    }

    // İleri veya geri git
    if (steps >= 0)
    {
        while (steps > 0)
        {
            start = start->next;
            steps--;
        }
    }
    else
    {
        while (steps < 0)
        {
            start = start->prev;
            steps++;
        }
    }

    return start;
}
int KromozomList::Count() const
{
    return size;
}
bool KromozomList::isEmpty() const
{
    return size == 0;
}
void KromozomList::add(const GenList &genList) throw(NoSuchElement)
{
    GenList *yeniGenList = new GenList(genList);
    KromozomNode *yeniDugum = new KromozomNode(yeniGenList);

    if (size == 0) // Liste boşsa
    {
        head = yeniDugum;
        head->next = head; // Kendisine bağla
        head->prev = head; // Kendisine bağla
    }
    else // Liste doluysa
    {
        KromozomNode *last = head->prev; // Son düğümü bul (tail yerine)

        // Yeni düğümü sona ekle
        last->next = yeniDugum;
        yeniDugum->prev = last;
        yeniDugum->next = head;
        head->prev = yeniDugum;
    }

    size++;
    if (size % 100 == 0)
    {
        updateReferencePoints();
    }
}

void KromozomList::removeAt(int index) throw(NoSuchElement)
{
    if (index < 0 || index >= size)
        throw NoSuchElement("No Such Element");
    KromozomNode *del;
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
        KromozomNode *prv = FindPreviousByPosition(index);
        del = prv->next;
        prv->next = del->next;
        del->next->prev = prv;
    }
    size--;
    delete del;
}
void KromozomList::clear()
{
    while (!isEmpty())
    {
        removeAt(0);
    }
}
KromozomList::~KromozomList()
{
    clear();
}