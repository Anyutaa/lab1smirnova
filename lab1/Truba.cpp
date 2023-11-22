#include "Truba.h"
#include <iostream> 
#include <fstream>
#include <string>
#include "utils.h"
#include <set>
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
	cerr << tr.name_truba << endl;
	cout << "Enter lenght (1.0, 10000.0):";
	tr.lenght = GetCorrect(1.0, 10000.0);
	cout << "Enter diametr (1, 1400):";
	tr.diametr = GetCorrect(1, 1400);
	cout << "Enter repair (0, 1):";
	tr.repair = GetCorrect(0, 1);
	return in;
}

ostream& operator << (ostream& out, const Truba& tr)
{
	if ((tr.name_truba) == "None")
	{
		out << "You do not have pipe" << endl;
		return out;
	}
	out << "\nMaxID: " << Truba::MaxIDTruba
		<< "\nID: " << tr.idpipe
		<< "\nPipe name: " << tr.name_truba
		<< "\nPipe length: " << tr.lenght
		<< "\nPipe diameter: " << tr.diametr
		<< "\nThe pipe attribute: " << tr.repair << endl;
	return out;
}

void DataRecordingPipe(ofstream& fout, const Truba& pipe) {

	if (pipe.name_truba.empty())
	{
		cout<<"You don't have the pipe to save"<<endl;
	}
	else
	{
		fout << "Pipe:" << endl;
		fout << pipe.MaxIDTruba << endl << pipe.idpipe << endl << pipe.name_truba << endl << pipe.lenght << endl << pipe.diametr << endl << pipe.repair << endl;
	}
}
