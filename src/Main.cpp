#pragma GCC diagnostic ignored "-Wdeprecated"
#include <cstdlib>
#include <algorithm>
#include "../include/Kromozom/KromozomList.hpp"
#include "../include/Gen/GenList.hpp"

int main()
{

	KromozomList *kromozomlar = new KromozomList();
	ifstream dnaFile("Dna.txt"); // Dna.txt dosyasını aç

	if (!dnaFile.is_open())
	{
		cout << "Dosya açılamadı! Dosya mevcut mu ve doğru dizinde mi?" << endl;
		return 1;
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

	int choice = 0;
	int satir1 = 0;
	int satir2 = 0;
	int satir = 0;
	int sutun = 0;
	do
	{
		cout << "[1]\tCaprazlama" << endl;
		cout << "[2]\tMutasyon" << endl; /* doğru çalışıyor delete bakılcak */
		cout << "[3]\tOtomatik Islemler" << endl;
		cout << "[4]\tEkrana Yaz" << endl; /* doğru çalışıyor delete bakılcak */
		cout << "[5]\tExit" << endl;
		cout << "Choice:";
		cin >> choice;
		try
		{
			switch (choice)

			{
			case 1:

				cout << "Birinci kromozom indexi:";
				cin >> satir1;
				cout << "Ikinci kromozom indexi:";
				cin >> satir2;
				kromozomlar->Caprazlama(satir1, satir2);
				break;
			case 2:

				cout
					<< "Mutasyon yapilacak kromozom satırı:";
				cin >> satir;
				cout << "Mutasyon yapılacak genin sütun numarası:";
				cin >> sutun;
				kromozomlar->Mutasyon(satir, sutun);
				break;
			case 3:
				kromozomlar->processCommands(*kromozomlar);
				break;
			case 4:
				kromozomlar->yazdir();
				break;
			case 5:
				break;

			default:
				cout << endl
					 << "Wrong choice!!" << endl;
				cin.ignore();
				cin.get();
				break;
			}
		}
		catch (const char *e)
		{
			cout << "Error:" << e << endl;
			cin.get();
		}
		catch (const exception &e)
		{
			cout << "Standart Exception: " << e.what() << endl;
		}
		catch (const NoSuchElement &e)
		{
			cout << "Hata: " << e.Message() << endl;
		}
	} while (choice != 5);

	delete kromozomlar;
	return 0;
}