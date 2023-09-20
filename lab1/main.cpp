#include <iostream> 
#include <fstream>
using namespace std;

struct Truba 
{
	string otmetka;
	double dlina;
	int diametr;
	bool remont;
};

struct KC 
{
	string nazvanKC;
	int kolvotsekh;
	int tsekhvrabote;
	char effect;
};

Truba vvod_truba()
{
	Truba tr;
	cout << "Enter otmetky:";
	cin >> tr.otmetka;
	cout << "Enter dlina:";
	cin >> tr.dlina;
	cout << "Enter diametr:";
	cin >> tr.diametr ;
	cout << "Enter remont:";
	cin >> tr.remont;
	return tr;

};

KC vvod_KC()
{
	KC kc;
	cout << "Enter nazvanie KC:";
	cin >> kc.nazvanKC;
	cout << "Enter kolvo tsekhov:";
	cin >> kc.kolvotsekh;
	cout << "Enter tsekh v rabote:";
	cin >> kc.tsekhvrabote;
	cout << "Enter effect:";
	cin >> kc.effect;
	return kc;
};

void Print_truba(Truba tr)
{
	cout << "Enter otmetky:" << tr.otmetka
		<< "\tEnter dlina:" << tr.dlina
		<< "\tEnter diametr:" << tr.diametr
		<<"\tEnter remont : " << tr.remont<<endl;
};

void Print_KC(KC kc)
{
	cout << "Enter nazvanie KC:" << kc.nazvanKC
		<< "\tEnter kolvo tsekhov:" << kc.kolvotsekh
		<< "\tEnter tsekh v rabote:" << kc.tsekhvrabote
		<< "\tEnter effect: " << kc.effect << endl;
};

int Vvod_vibor()
{
	cout << "Select: ";
	int vibor = 0;
	cin >> vibor;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Try again \n";
		cin >> vibor;
	}
	return vibor;
}

int main()
{
	cout << "Select menu item:" 
		<<"\n1. Add pipe"
		<<"\n2. Add KS"
		<<"\n3. View all objects"
		<<"\n4. Edit pipe"
		<<"\n5. Edit KS"
		<<"\n6. Save"
		<<"\n7. Dowload"
		<<"\n8. Exit" << endl;


	switch (Vvod_vibor())
	{
	case 1:
	{
		cout << "1. Add pipe"<< endl;
		Truba tr = vvod_truba();
		main();
		break;
	}
	case 2:
	{
		cout << "2. Add KS" << endl;
		KC kc = vvod_KC();
		main();
		break;
	}
	case 3:
	{
		cout << "3. View all objects" << endl;
		main();
		break;
	}
	case 4:
	{
		cout << "4. Edit pipe" << endl;
		main();
		break;
	}
	case 5:
	{
		cout << "5. Edit KS" << endl;
		main();
		break;
	}
	case 6:
	{
		cout << "6. Save" << endl;
		main();
		break;
	}
	case 7:
	{
		cout << "7. Dowload" << endl;
		main();
		break;
	}
	case 8:
	{
		cout << "8. Exit" << endl;
		break;
	}
	default:
	{
		cout << "Entry a number from  1 to 8 "<<endl;
		switch (Vvod_vibor());
		break;
	}
	}
	/*Truba tr = vvod_truba();
	Print_truba(tr);
	

	KC kc = vvod_KC();
	Print_KC(kc);*/
	

	return 0;
}