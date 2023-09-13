#include <iostream> 
#include <vector>
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

int main()
{
	Truba tr = vvod_truba();
	Print_truba(tr);
	/*vector <Truba> truboprovod;
	size_t n = 0;
	cin >> n;
	truboprovod.resize(n);*/

	KC kc = vvod_KC();
	Print_KC(kc);
	/*vector <KC> KCgroup;
	size_t m = 0;
	cin >> m;
	KCgroup.resize(m);*/

	return 0;
}