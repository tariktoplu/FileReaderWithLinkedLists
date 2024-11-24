#pragma GCC diagnostic ignored "-Wdeprecated"
#include <algorithm>
#include <iostream>
#include <fstream>
#include "../include/Kromozom/KromozomList.hpp"
#include "../include/Gen/GenList.hpp"

using namespace std;

void displayMenu()
{
	cout << "[1]\tCaprazlama" << endl;
	cout << "[2]\tMutasyon" << endl;
	cout << "[3]\tOtomatik Islemler" << endl;
	cout << "[4]\tEkrana Yaz" << endl;
	cout << "[5]\tExit" << endl;
}

void handleChoice(KromozomList *kromozomlar, int choice)
{
	int satir1 = 0, satir2 = 0, satir = 0, sutun = 0;

	switch (choice)
	{
	case 1:
		cout << "Birinci kromozom indexi: ";
		cin >> satir1;
		cout << "Ikinci kromozom indexi: ";
		cin >> satir2;
		kromozomlar->Caprazlama(satir1, satir2);
		break;
	case 2:
		cout << "Mutasyon yapilacak kromozom satırı: ";
		cin >> satir;
		cout << "Mutasyon yapılacak genin sütun numarası: ";
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
		cout << "Wrong choice!!" << endl;
		break;
	}
}

int main()
{
	KromozomList *kromozomlar = new KromozomList();
	ifstream dnaFile("Dna.txt");

	if (!dnaFile.is_open())
	{
		cerr << "Dosya açılamadı! Dosya mevcut mu ve doğru dizinde mi?" << endl;
		return 1;
	}

	string line;
	while (getline(dnaFile, line))
	{
		line.erase(remove(line.begin(), line.end(), ' '), line.end());
		if (line.empty())
			continue;

		GenList *genList = new GenList();
		for (char gene : line)
		{
			genList->add(gene);
		}
		kromozomlar->add(*genList);
		delete genList;
	}

	dnaFile.close();

	int choice = 0;
	do
	{
		displayMenu();
		cout << "Choice: ";
		cin >> choice;

		try
		{
			handleChoice(kromozomlar, choice);
		}
		catch (const char *e)
		{
			cerr << "Error: " << e << endl;
		}
		catch (const exception &e)
		{
			cerr << "Standart Exception: " << e.what() << endl;
		}
		catch (const NoSuchElement &e)
		{
			cerr << "Hata: " << e.Message() << endl;
		}
	} while (choice != 5);

	delete kromozomlar;
	return 0;
}