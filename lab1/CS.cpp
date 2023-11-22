#include "CS.h"
#include <iostream> 
#include <fstream>
#include "utils.h"
#include <set>
using namespace std;

int CS::MaxIDCS = 0;

CS::CS()
{
	idcs = MaxIDCS++;
}

istream& operator >> (istream& in,  CS& cs)
{
	cout << "Enter name CS:";
	cin.ignore();
	getline(cin, cs.name_cs);
	cerr << cs.name_cs << endl;
	cout << "Enter workshops (1, 1000):";
	cs.workshops = GetCorrect(1, 1000);
	cout << "Enter workshops in work (0-" << cs.workshops << ")"<<endl;
	cs.workshops_work = GetCorrect(0, cs.workshops);
	cout << "Enter effect ('A', 'D'):";
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

void DataRecordingCS(ofstream& fout, const CS& cs) {

	if (cs.name_cs.empty())
	{
		cout << "You don't have the pipe to save" << endl;


	}
	else
	{
		fout << "Station:" << endl;
		fout << cs.MaxIDCS << endl << cs.idcs << endl << cs.name_cs << endl << cs.workshops << endl << cs.workshops_work << endl << cs.effect << endl;
	}
}

