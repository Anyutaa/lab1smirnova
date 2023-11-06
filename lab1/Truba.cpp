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

void Add_pipe(unordered_map < int, Truba >& pipes) {
	Truba pipe;
	cout << "1. Add pipe" << endl;
	cin >> pipe;
	pipes.insert({ pipe.get_idp(),pipe });
}

void OutputPipe(unordered_map <int, Truba>& p)
{
	if ((p.size()) == 0)
	{
		cout << "You do not have pipe" << endl;
	}
	else
		for (auto x : p)
			cout << x.first << " " <<
			x.second << endl;
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

ostream& operator << (ostream& out, const Truba& tr)
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

void Writing_to_file_pipe(unordered_map <int, Truba>& p)
{
	ofstream fout("lab_smirnova.txt");
	if ((p.size()) == 0)
	{
		cout << "No information about pipe " << endl;
		return;
	}
	cout << "Add information about pipe " << endl;
	fout << "Pipes" << endl;
	for (auto x : p)
		fout << x.first << " " << x.second << endl;

	fout.close();
}

void Read_from_file_pipe(unordered_map <int, Truba>& p)
{
	ifstream fin("lab_smirnova.txt");
	if (fin)
	{
		string name_of_truba = "none";
		bool kp = 0;
		while (getline(fin, name_of_truba))
		{
			if (name_of_truba == "Pipe: ")
			{
				Truba pipe;
				int m = 0;
				fin >> m;
				fin >> pipe.MaxIDTruba;
				fin >> pipe.idpipe;
				getline(fin, pipe.name_truba);
				fin >> pipe.lenght;
				fin >> pipe.diametr;
				fin >> pipe.repair;
				p.insert({ m,pipe });
				kp = true;
			}
		}
		if (!kp)
		{
			cout << "No information about pipe." << endl;
		}
		else
			return OutputPipe(p);
	}
	fin.close();
}
