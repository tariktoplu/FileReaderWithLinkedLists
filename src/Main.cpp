#pragma GCC diagnostic ignored "-Wdeprecated"
#include <cstdlib>
#include <algorithm>
#include "../include/Kromozom/KromozomList.hpp"
#include "../include/Gen/GenList.hpp"

// Hata mesajını yazdır ve devam et
void handleError(const string &errorMessage)
{
	cout << "Hata: " << errorMessage << endl;
}

// Dosyadan KromozomList'e verileri okuma fonksiyonu
int ReadFile(KromozomList *kromozomlar)
{
	try
	{
		ifstream dnaFile("Dna.txt"); // Dna.txt dosyasını aç

		if (!dnaFile.is_open())
		{
			handleError("Dosya açılamadı! Dosya mevcut mu ve doğru dizinde mi?");
			return 1; // Hata durumunda 1 döndür
		}

		string line;
		while (getline(dnaFile, line))
		{
			// Satırdaki boşlukları kaldır
			line.erase(remove(line.begin(), line.end(), ' '), line.end());

			// Eğer satır boşsa (sadece boşluklardan oluşuyorsa), işlemi atla
			if (line.empty())
				continue;

			GenList *genList = new GenList(); // Yeni bir GenList oluştur
			for (char gene : line)
			{
				genList->add(gene); // Geni GenList'e ekle
			}
			kromozomlar->add(genList); // Oluşturulan GenList'i KromozomList'e ekle
		}
		dnaFile.close();
	}
	catch (const exception &e)
	{
		handleError(e.what());
		return 1; // Hata durumunda 1 döndür
	}
	return 0; // Başarılı bir şekilde okuma yapıldıysa 0 döndür
}

// Kullanıcıdan seçim alma ve işlemleri gerçekleştirme fonksiyonu
void handleUserChoice(KromozomList *kromozomlar)
{
	int choice = 0;
	do
	{
		cout << "[1]\tCaprazlama" << endl;
		cout << "[2]\tMutasyon" << endl;
		cout << "[3]\tOtomatik Islemler" << endl;
		cout << "[4]\tEkrana Yaz" << endl;
		cout << "[5]\tExit" << endl;
		cout << "Choice: ";
		cin >> choice;

		try
		{
			switch (choice)
			{
			case 1:
			{
				int satir1, satir2;
				cout << "Birinci kromozom indexi: ";
				cin >> satir1;
				cout << "Ikinci kromozom indexi: ";
				cin >> satir2;
				kromozomlar->Caprazlama(satir1, satir2);
			}
			break;

			case 2:
			{
				int satir, sutun;
				cout << "Mutasyon yapilacak kromozom satırı: ";
				cin >> satir;
				cout << "Mutasyon yapılacak genin sütun numarası: ";
				cin >> sutun;
				kromozomlar->Mutasyon(satir, sutun);
			}
			break;

			case 3:
				kromozomlar->processCommands(*kromozomlar);
				break;

			case 4:
				kromozomlar->yazdir();
				break;

			case 5:
				cout << "Çıkılıyor..." << endl;
				break;

			default:
				cout << "Geçersiz seçim! Lütfen tekrar deneyin." << endl;
				break;
			}
		}
		catch (const char *e)
		{
			handleError(e);
		}
		catch (const exception &e)
		{
			handleError(e.what());
		}
		catch (const NoSuchElement &e)
		{
			handleError(e.Message());
		}
	} while (choice != 5);
}

int main()
{
	KromozomList *kromozomlar = new KromozomList(); // KromozomList nesnesi oluştur

	// Dosyadan verileri oku
	if (ReadFile(kromozomlar) != 0)
	{
		delete kromozomlar;
		return 1; // Okuma hatası varsa çık
	}

	// Kullanıcıdan seçim al ve işlemleri gerçekleştir
	handleUserChoice(kromozomlar);

	// Bellek temizliği
	delete kromozomlar; // KromozomList nesnesini serbest bırak
	return 0;			// Program başarıyla tamamlandı
}