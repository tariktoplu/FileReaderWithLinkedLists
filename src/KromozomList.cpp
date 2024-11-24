
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
            continue;
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
    if (index <= 0 || index > size) // Geçersiz indeks kontrolü
        throw NoSuchElement("No Such Element");

    KromozomNode *current = head;

    // Circular doubly linked list olduğu için, head'e dönebiliriz
    for (int i = 0; i < index - 1; i++)
    {
        current = current->next; // Sonraki düğüme geç
    }

    return current; // Önceki düğümü döndür
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
    if (index1 < 0 || index2 >= size || index2 < 0 || index2 >= size)
        throw "Hatali Konum Bilgisi";

    KromozomNode *kromozom1 = head;
    KromozomNode *kromozom2 = head;

    for (int i = 0; i < index1; i++)
        kromozom1 = kromozom1->next;
    for (int i = 0; i < index2; i++)
        kromozom2 = kromozom2->next;

    GenList *caprazlananKromozom1 = new GenList();
    GenList *caprazlananKromozom2 = new GenList();

    int orta1 = kromozom1->genList->Count() / 2;
    int orta2 = kromozom2->genList->Count() / 2;

    GenNode *gezici = kromozom1->genList->first();
    for (int i = 0; i < orta1; i++)
    {
        caprazlananKromozom1->add(gezici->data);
        gezici = gezici->next;
    }

    gezici = kromozom2->genList->first();
    for (int i = 0; i < orta2; i++)
        gezici = gezici->next;
    for (int i = orta2; i < kromozom2->genList->Count(); i++)
    {
        caprazlananKromozom1->add(gezici->data);
        gezici = gezici->next;
    }

    gezici = kromozom2->genList->first();
    for (int i = 0; i < orta2; i++)
    {
        caprazlananKromozom2->add(gezici->data);
        gezici = gezici->next;
    }

    gezici = kromozom1->genList->first();
    for (int i = 0; i < orta1; i++)
        gezici = gezici->next;
    for (int i = orta1; i < kromozom1->genList->Count(); i++)
    {
        caprazlananKromozom2->add(gezici->data);
        gezici = gezici->next;
    }

    this->add(*caprazlananKromozom1);
    this->add(*caprazlananKromozom2);

    delete caprazlananKromozom1;
    delete caprazlananKromozom2;
}
void KromozomList::Mutasyon(int kromozomIndex, int genIndex)
{
    if (kromozomIndex < 0 || kromozomIndex >= size)
    {
        throw "Kromozom indeksi geçersiz!";
    }

    KromozomNode *kromozom = head;
    for (int i = 0; i < kromozomIndex; i++)
    {
        kromozom = kromozom->next;
    }

    // Kromozom içindeki gen listesini al
    GenList *genListe = kromozom->genList;

    if (genIndex < 0 || genIndex >= genListe->Count())
    {
        throw "Gen indeksi geçersiz!";
    }

    // Belirtilen genin değerini "X" olarak değiştir
    GenNode *genDugum = genListe->first();
    for (int i = 0; i < genIndex; i++)
    {
        genDugum = genDugum->next;
    }

    genDugum->data = 'X'; // Gen değerini "X" olarak değiştir
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
            start = head->prev;
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

    if (size == 0)
    {
        // Liste boşsa, yeni düğüm kendisine işaret eder
        yeniDugum->next = yeniDugum;
        yeniDugum->prev = yeniDugum;
        head = yeniDugum; // Yeni düğüm baş düğüm oldu
    }
    else
    {
        // Liste doluysa, yeni düğüm başa eklenir
        yeniDugum->next = head;
        yeniDugum->prev = head->prev; // Yeni düğümün önceki düğümünü ayarla
        head->prev->next = yeniDugum; // Eski başın önceki düğümü yeni düğüme bağla
        head->prev = yeniDugum;       // Eski başın önceki düğümünü yeni düğüme bağla
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
    {
        throw "Index out of Range";
    }

    KromozomNode *del;

    if (size == 1)
    {
        // Eğer sadece bir eleman varsa
        del = head;
        head = nullptr; // Listeyi boşalt
    }
    else if (index == 0)
    {
        // İlk elemanı silme durumu
        del = head;
        head = head->next; // Yeni baş düğüm
        // Yeni baş düğümün önceki bağlantısını güncelle
        head->prev = del->prev; // Yeni başın önceki bağlantısını eski başın öncesine ayarla
        // Eski başın son düğüm ile bağlantısını güncelle
        del->prev->next = head;
    }
    else
    {
        // Diğer durumlar
        KromozomNode *prv = FindPreviousByPosition(index);
        del = prv->next;
        prv->next = del->next; // Önceki düğümün sonraki bağlantısını güncelle
        del->next->prev = prv; // Sonraki düğümün önceki bağlantısını güncelle
    }

    delete del->genList; // Kromozom verisini sil
    delete del;          // Düğümü sil
    size--;
}
void KromozomList::clear()
{
    while (!isEmpty())
        removeAt(0);
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