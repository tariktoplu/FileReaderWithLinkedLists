#pragma GCC diagnostic ignored "-Wdeprecated"
#include <cstdlib>
#include "../include/Kromozom/KromozomList.hpp"

int main()
{
	KromozomList *kromozomlar = new KromozomList();
	ifstream dnaFile("Dna.txt"); // Dna.txt dosyasını aç

	if (!dnaFile.is_open())
	{
		cout << "Dosya açılamadı!" << endl;
		return 1;
	}

	string line;
	while (getline(dnaFile, line))
	{									  // Her satırı oku
		GenList *genList = new GenList(); // Yeni bir GenList oluştur
		for (char gene : line)
		{						// Satırdaki her harfi (geni) oku
			genList->add(gene); // Geni GenList'e ekle
		}
		kromozomlar->add(genList); // Oluşturulan GenList'i KromozomList'e ekle
	}

	dnaFile.close(); // Dosyayı kapat

	// Kromozomları ekrana yazdır
	cout << *kromozomlar; /*
	 int choice = 0;
	 int satir1 = 0;
	 int satir2 = 0;
	 int satir = 0;
	 int sutun = 0;
	 do
	 {
		 // system("CLS");
		 cout << "[1]\tCaprazlama" << endl;
		 cout << "[2]\tMutasyon" << endl;
		 cout << "[3]\tOtomatik Islemler" << endl;
		 cout << "[4]\tEkrana Yaz" << endl;
		 cout << "[5]\tExit" << endl;
		 cout << "Choice:";
		 cin >> choice;
		 // system("CLS");
		 try
		 {
			 switch (choice)

			 {
			 case 1:

				 cout << "Birinci kromozom satırı:";
				 cin >> satir1;
				 cout << "Ikinci kromozom satırı:";
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
				 kromozomlar->OtomatikIslemler();
				 break;
			 case 4:
				 cout << *kromozomlar;
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
		 // system("CLS");
	 } while (choice != 5); */
	delete kromozomlar;
	return 0;
}