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

istream& operator >> (istream& in, CS& cs)
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

ostream& operator << (ostream& out, CS& cs)
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