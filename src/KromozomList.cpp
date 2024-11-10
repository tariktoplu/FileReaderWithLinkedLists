
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
}
/* bu çaprazlama bitti gibi */
void KromozomList::Caprazlama(int index1, int index2)
{
    if (index1 < 0 || index1 > size || index2 < 0 || index2 > size)
    {
        throw NoSuchElement("Invalid index for crossover.");
    }
    /* satır 1 girilince noluyor denemek lazım */
    KromozomNode *kromozom1 = FindFromNodeByPosition(index1);
    KromozomNode *kromozom2 = FindFromNodeByPosition(index2);

    if (kromozom1 == nullptr || kromozom2 == nullptr)
    {
        throw NoSuchElement("Kromozom not found.");
    }
    GenList *genList1 = kromozom1->genList;
    GenList *genList2 = kromozom2->genList;
    genList1->Caprazlama(genList1, genList2, *this);
}

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
/* KromozomNode *FindNodeByPosition(int index)
{
    if (index < 0 || index >= size)
        throw NoSuchElement("No Such Element");

    // Liste boyutunun çeyrekleri
    int quarter = size / 4;
    int mid = size / 2;
    int threeQuarter = 3 * quarter;

    KromozomNode *itr;
    int steps;

    // İlk çeyrek
    if (index < quarter)
    {
        itr = head;
        for (int i = 0; i < index; i++)
        {
            itr = itr->next;
        }
    }
    // İkinci çeyrek
    else if (index < mid)
    {
        // quarterNode'dan başla (zaten elimizde var)
        itr = quarterNode; // Artık head'den başlamıyoruz!
        for (int i = quarter; i < index; i++)
        {
            itr = itr->next;
        }
    }
    // Üçüncü çeyrek
    else if (index < threeQuarter)
    {
        // midNode'dan başla (zaten elimizde var)
        itr = midNode; // Artık head'den başlamıyoruz!
        for (int i = mid; i < index; i++)
        {
            itr = itr->next;
        }
    }
    // Son çeyrek
    else
    {
        // threeQuarterNode'dan başla veya sondan yaklaşalım
        if (index - threeQuarter < size - index)
        {
            // 3/4 noktasından başlamak daha yakınsa
            itr = threeQuarterNode; // Artık head'den başlamıyoruz!
            for (int i = threeQuarter; i < index; i++)
            {
                itr = itr->next;
            }
        }
        else
        {
            // Sondan başlamak daha yakınsa
            itr = head->prev;
            for (int i = size - 1; i > index; i--)
            {
                itr = itr->prev;
            }
        }
    }

    return itr;
} */

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

void KromozomList::add(GenList *genList) throw(NoSuchElement)
{
    if (size == 0) // Liste boşsa
    {
        head = new KromozomNode();
        head->genList = genList;
        head->next = head->prev = head;
    }
    else // Liste doluysa, en sona ekle
    {
        KromozomNode *last = head->prev;                      // Son düğümü bul
        KromozomNode *newNode = new KromozomNode(head, last); // Yeni düğüm oluştur ve son düğümün arkasına ekle
        newNode->genList = genList;
        last->next = newNode;
        head->prev = newNode;
    }
    size++;

    if (size % 100 == 0)
    {
        updateReferencePoints();
    }
}

void KromozomList::removeAt() throw(NoSuchElement)
{
    KromozomNode *del;

    del = head;
    if (size == 1)
        head = NULL;
    else
    {
        head = head->next;
        head->prev = del->prev;
        del->prev->next = head;
    }

    size--;
    delete del->genList;
    delete del;
}
void KromozomList::clear()
{
    while (!isEmpty())
        removeAt();
}
ostream &operator<<(ostream &screen, KromozomList &rgt)
{
    int index = 0;
    for (KromozomNode *itr = rgt.head; index < rgt.size; itr = itr->next, index++)
    {
        screen << *(itr->genList) << " <-> "; /* yazabilir emin değilim */
    }
    screen << endl;
    return screen;
}
KromozomList::~KromozomList()
{
    clear();
}