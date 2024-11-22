#pragma GCC diagnostic ignored "-Wdeprecated"
#include <cstdlib>
#include <algorithm>
#include "../include/Kromozom/KromozomList.hpp"
#include "../include/Gen/GenList.hpp"
#include <chrono>
#include <memory>
// Hata mesajını yazdır ve devam et
void handleError(const string &errorMessage)
{
	cout << "Hata: " << errorMessage << endl;
}
/*eski fonk
// Dosyadan KromozomList'e verileri okuma fonksiyonu
int ReadFile(KromozomList *kromozomlar)
{
	try
	{
		auto start = std::chrono::high_resolution_clock::now();
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
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> duration = end - start;

		// Okuma süresini ekrana yazdır
		std::cout << "Dosya okuma süresi: " << duration.count() << " saniye\n";
	}
	catch (const exception &e)
	{
		handleError(e.what());
		return 1; // Hata durumunda 1 döndür
	}
	return 0; // Başarılı bir şekilde okuma yapıldıysa 0 döndür
} */
/*
int ReadFile(KromozomList *kromozomlar)
{
	try
	{
		auto start = chrono::high_resolution_clock::now();

		basic_filebuf<char> filebuf;
		filebuf.open("Dna.txt", ios::in | ios::binary);

		if (!filebuf.is_open())
		{
			handleError("Dosya açılamadı! Dosya mevcut mu ve doğru dizinde mi?");
			return 1;
		}

		GenList *currentList = new GenList();

		// Dosyayı karakter karakter işle
		while (true)
		{
			int c = filebuf.sbumpc(); // Bir karakter oku

			if (c == EOF)
				break;

			// Satır sonlarını ve boşluk karakterlerini atla
			if (c == '\n' || c == '\r' || c == ' ' || c == '\t')
			{
				if (c == '\n' || c == '\r') // Yeni satır varsa listeyi ekle
				{
					kromozomlar->add(*currentList);
					currentList = new GenList(); // Yeni GenList başlat

					// Windows'ta \r\n kontrolü
					if (c == '\r' && filebuf.sgetc() == '\n')
					{
						filebuf.sbumpc(); // \n karakterini atla
					}
				}
				continue;
			}

			// Geçerli karakteri listeye ekle
			currentList->add(static_cast<char>(c));
		}

		// Son listeyi ekle
		kromozomlar->add(*currentList);

		filebuf.close();

		auto end = chrono::high_resolution_clock::now();
		chrono::duration<double> duration = end - start;

		cout << "Dosya okuma süresi: " << duration.count() << " saniye\n";
	}
	catch (const exception &e)
	{
		handleError(e.what());
		return 1;
	}
	return 0;
} */
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
	ifstream dnaDosyasi("Dna.txt");
	string satir;
	if (dnaDosyasi.is_open())
	{
		while (getline(dnaDosyasi, satir))
		{
			GenList *genList = new GenList();
			for (char gen : satir)
			{
				if (gen != ' ')
				{
					genList->add(gen);
				}
			}
			kromozomlar->add(*genList);
			delete genList;
		}
		dnaDosyasi.close();
	}
	else
	{
		cerr << "DNA dosyasi acilamadi!" << endl;
	}

	// Kullanıcıdan seçim al ve işlemleri gerçekleştir
	handleUserChoice(kromozomlar);

	// Bellek temizliği
	delete kromozomlar; // KromozomList nesnesini serbest bırak
	return 0;			// Program başarıyla tamamlandı
}