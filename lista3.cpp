//Rafal Kubala 3b
//asd
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct SElement
{
	string imie;
	string nazwisko;
	int status;
	SElement *next;
	SElement *prev;

};

SElement *head = nullptr;
SElement *tail = head;
SElement *current = nullptr;

void dodaj(string imie, string nazwisko, int status = 1)
{
	SElement *tmp = new SElement;
	tmp->imie = imie;
	tmp->nazwisko = nazwisko;
	tmp->status = status;
	tmp->next = nullptr;

	if (head == nullptr)
	{
		head = tmp;
		tail = tmp;
		tmp->prev = nullptr;
	}
	else
	{
		tail->next = tmp;
		tmp->prev = tail;
		tail = tmp;
	}

}

void usun()
{
	current = head;
	if (current == nullptr)
	{
		cout << "Niema czego usunac (lista jest pusta)\n";
	}
	else
	{

		SElement *tmp = current;
		current = current->prev;

		if (tmp == head)
		{
			if (head->next == nullptr)
			{
				head = nullptr;
				tail = head;
			}
			else
			{
				head = tmp->next;
				head->prev = nullptr;
			}
		}
		else if (tmp != tail)
		{
			tmp->prev->next = tmp->next;
			tmp->next->prev = tmp->prev;
		}
		else
		{
			current->next = nullptr;
			tail = current;
		}

		delete tmp;
	}
}
void wyswietlListe()
{
	current = head;
	int i = 1;
	if (current == nullptr)
	{
		cout << "Lista pusta (Dodaj osobe)\n";

	}
	else
	{
		cout << "Lp." << "		" << "imie" << "		" << "nazwisko" << "		" << "status" << endl;
		while (current->next != nullptr)
		{
			if (current->status == 1)
			{
				cout << i << "		" << current->imie << "		" << current->nazwisko << "			" << "Obecny" << endl;
				current = current->next;
				i++;
			}
			else
			{
				cout << i << "		" << current->imie << "		" << current->nazwisko << "			" << "Nieobecny" << endl;
				current = current->next;
				i++;
			}
		}
		if (current->status == 1)
		{
			cout << i << "		" << current->imie << "		" << current->nazwisko << "			" << "Obecny" << endl;
			current = current->next;
		}
		else
		{
			cout << i << "		" << current->imie << "		" << current->nazwisko << "			" << "Nieobecny" << endl;
			current = current->next;
		}

	}
}



void sprawdzObecnosc()
{

	current = head;
	int i = 1;
	if (current == nullptr)
	{
		cout << "lista jest pust\n";
	}
	else
	{
		cout << "Lp." << " " << "imie" << " " << "nazwisko" << " " << "status" << endl;
		while (current->next != nullptr)
		{

			cout << i << " " << current->imie << " " << current->nazwisko << " ";
			cout << "jest obecny? (1 - Tak 0 - Nie)";
			cin >> current->status;
			i++;
		}

		cout << i << " " << current->imie << " " << current->nazwisko << " ";
		cout << " jest obecny? (1 - Tak 0 - Nie)";
		cin >> current->status;
	}


}

void usunZlisty()
{
	current = head;
	
	if (current->status <= 0)
	{
		usun();
			
	}
	else
	{
		current = current->next;
	}
	
}



void zapisz()
{
	current = head;
	ofstream zapis;
	zapis.open("lista.txt");
	if (head == nullptr)
	{
		cout << "lista jest pusta\n";
		zapis << "Lp." << "		" << "imie" << "		" << "nazwisko" << "		" << "status\n";
	}
	else
	{
		int i = 1;
		ofstream zapis;
		zapis.open("lista.txt");

		if (zapis.good())
		{
			zapis << "Lp." << "		" << "imie" << "		" << "nazwisko" << "		" << "status\n";
			while (current->next != nullptr)
			{
				zapis << i << "		" << current->imie << "			" << current->nazwisko << "		" << current->status << endl;
				current = current->next;
				i++;
			}
			zapis << i << "		" << current->imie << "			" << current->nazwisko << "		" << current->status << endl;

		}
		else cout << "Blad pliku";
	}
	zapis.close();
}
void wyczyscListe()
{
	while (head != tail)
	{
		current = tail->prev;
		delete tail;
		tail = current;
	}
	delete tail;
	head = nullptr;
	tail = head;
	current = nullptr;
}
void wczytaj()
{
	char litera;
	if (head == nullptr)
	{
		litera = 't';
	}
	else
	{
		cout << "Obecnie lista jest wypelniona danymi,\njezeli bedziesz kontynuowal stracisz te dane.\nCzy mimo to kontynuowac?(t-tak, n-nie):";
		cin >> litera;
		if (litera == 't')
			wyczyscListe();
	}
	switch (litera)
	{
	case 't':
		ifstream odczyt;
		odczyt.open("plik.txt");
		if (odczyt.good())
		{
			string imie, nazwisko, linijka;
			int status, dlugosc;
			odczyt.seekg(0, ios::end);
			dlugosc = odczyt.tellg();
			odczyt.seekg(0, ios::beg);
			getline(odczyt, linijka);

			while (odczyt.tellg() < (dlugosc - 10) && odczyt.tellg() >= 0)
			{
				odczyt >> linijka;
				odczyt >> imie;
				odczyt >> nazwisko;
				odczyt >> status;
				dodaj(imie, nazwisko, status);

			}
			cout << "\nWczytano nastepujace dane:\n";
			wyswietlListe();
		}
		else cout << "Blad";
	}

}
void mainMenu()
{
	cout << "Menu:\n";
	cout << "1. Usun pierwsza osobe\n";
	cout << "2. Dodaj 1-osobe\n";
	cout << "3. Dodaj wiecej osob\n";
	cout << "4. Sprawdz obecnosc\n";
	cout << "5. Wyswietl liste\n";
	cout << "6. Zapisz liste\n";
	cout << "7. Wczytaj liste\n";
	cout << "8. Wyczysc liste\n";
	cout << "9. Wyczysc ekran\n";
	cout << "0. Wyjdz\n";
}
int main()
{
	string imie, nazwisko;
	int i, x;
	do
	{
		current = nullptr;
		mainMenu();
		cin >> i;

		switch (i)
		{
		case 1:
			current = head;
			usun();
			current = nullptr;
			break;
		case 2:
			cout << "Podaj imie :";
			cin >> imie;
			cout << "Podaj nazwisko :";
			cin >> nazwisko;
			dodaj(imie, nazwisko);
			break;
		case 3:
			cout << "Podaj ile osob dodac :";
			cin >> i;
			while (i != 0)
			{
				cout << "Podaj imie :";
				cin >> imie;
				cout << "Podaj nazwisko :";
				cin >> nazwisko;
				dodaj(imie, nazwisko);
				i--;
			}
			break;


		case 4:
			sprawdzObecnosc();
			current = nullptr;
			break;

		case 5:
			wyswietlListe();
			current = nullptr;
			break;
		case 6:
			zapisz();
			break;
		case 7:
			wczytaj();
			break;
		case 8:
			wyczyscListe();
			break;
		case 9:
			system("cls");
			break;
		case 10:
			usunZlisty();
			break;
		default:
			return 0;
		}
		cout << endl;
	} while (i=!0);


}