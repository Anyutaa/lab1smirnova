#include "CS.h"
#include <iostream> 
#include <fstream>
#include "utils.h"
using namespace std;

int CS::MaxIDCS = 0;

CS::CS()
{
	idcs = MaxIDCS++;
}

void Add_cs(unordered_map < int, CS >& stations) {
	CS station;
	cout << "2. Add Cs" << endl;
	cin >> station;
	stations.insert({ station.get_idc(),station });
	
}

void OutputCs(unordered_map <int, CS>& s)
{
	if ((s.size()) == 0)
	{
		cout << "You do not have compressor station" << endl;
	}
	else
		for (auto x : s)
			cout << x.first << " " <<
			x.second << endl;

}

istream& operator >> (istream& in,  CS& cs)
{
	cout << "Enter name CS:";
	cin.ignore();
	getline(cin, cs.name_cs);
	cout << "Enter workshops:";
	cs.workshops = GetCorrect(1, 1000);
	cout << "Enter workshops in work:";
	cs.workshops_work = GetCorrect(0, cs.workshops);
	cout << "Enter effect:";
	cs.effect = GetCorrect('A', 'D');
	return in;
}

ostream& operator << (ostream& out, const CS& cs)
{
	if ((cs.name_cs) == "None")
	{
		out << "You do not have compressor station" << endl;
		return out;
	}
	/*out << "\nCompressor station:" << endl;*/
	out << "\nMaxID: " << CS::MaxIDCS
		<< "\nID: " << cs.idcs
		<< "\nCs name:" << cs.name_cs
		<< "\nNumber of workshops of the Cs:" << cs.workshops
		<< "\nNumber of workshops in operation of the Cs:" << cs.workshops_work
		<< "\nCS efficiency: " << cs.effect << endl;
	return out;
}

void Writing_to_file_cs(unordered_map <int, CS>& s)
{
	ofstream fout("lab_smirnova.txt", ios::app);
	if ((s.size()) == 0)
	{
		cout << "No information about station " << endl;
		return;
	}
	cout << "Add information about station " << endl;
	fout << "Stations" << endl;
	for (auto x : s)
		fout << "Station: \n" << x.first << " " << x.second << endl;
	fout.close();
}
void Read_from_file_cs(unordered_map <int, CS>& s)
{
	ifstream fin("lab_smirnova.txt");
	if (fin)
	{
		string name_of_cs = "none";
		bool ks = 0;
		while (getline(fin, name_of_cs))
		{
			if (name_of_cs == "Station: ")
			{
				CS cs;
				int m = 0;
				fin >> m;
				fin >> cs.MaxIDCS;
				fin >> cs.idcs;
				getline(fin, cs.name_cs);
				fin >> cs.workshops;
				fin >> cs.workshops_work;
				fin >> cs.effect;
				s.insert({ m,cs });
				ks = true;
			}
		}
		if (!ks)
		{
			cout << "No information about station." << endl;
		}
		else
			return OutputCs(s);
	}
	fin.close();
}