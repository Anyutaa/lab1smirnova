#include "Truba.h"
#include <iostream> 
#include <fstream>
#include "utils.h"
using namespace std;

int Truba::MaxIDTruba = 0;

Truba::Truba()
{
	idpipe = MaxIDTruba++;
}

istream& operator >> (istream& in, Truba& tr)
{
	cout << "Enter name truba:";
	cin.ignore();
	getline(cin, tr.name_truba);
	cout << "Enter lenght:";
	tr.lenght = GetCorrect(1.0, 10000.0);
	cout << "Enter diametr:";
	tr.diametr = GetCorrect(1, 1400);
	cout << "Enter repair:";
	tr.repair = GetCorrect(0, 1);
	return in;
}

ostream& operator << (ostream& out, Truba& tr)
{
	if ((tr.name_truba) == "None")
	{
		out << "You do not have pipe" << endl;
		return out;
	}

	/*out << "\nPipe:" << endl;*/
	out << "\nMaxID: " << Truba::MaxIDTruba
		<< "\nID: " << tr.idpipe
		<< "\nPipe name: " << tr.name_truba
		<< "\nPipe length: " << tr.lenght
		<< "\nPipe diameter: " << tr.diametr
		<< "\nThe pipe attribute: " << tr.repair << endl;
	return out;
}

//void Writing_to_file_pipe(unordered_map <int, Truba>& p)
//{
//	ofstream fout("lab_smirnova.txt");
//	if ((p.size()) == 0)
//	{
//		cout << "No information about pipe " << endl;
//		return;
//	}
//	cout << "Add information about pipe " << endl;
//	fout << "Pipes" << endl;
//	for (auto x : p)
//		fout << x.first << " " << x.second << endl;
//
//	fout.close();
//}

