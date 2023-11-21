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
	cout << "Enter workshops (1, 1000):";
	cs.workshops = GetCorrect(1, 1000);
	cout << "Enter workshops in work (0-" << cs.workshops << endl;
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

template<typename T>
using Filter = bool(*)(const CS& cs, T param);

bool CheckByName(const CS& cs, string param)
{
	return cs.name_cs.find(param) != string::npos;
}
bool CheckByWorshopsLess(const CS& tr, int param)
{
	return ((tr.workshops - tr.workshops_work) * 100 / tr.workshops) < param;
}
bool CheckByWorshopsEqual(const CS& tr, int param)
{
	return ((tr.workshops - tr.workshops_work) * 100 / tr.workshops) == param;
}
bool CheckByWorshopsMore(const CS& tr, int param)
{
	return ((tr.workshops - tr.workshops_work) * 100 / tr.workshops) > param;
}


template<typename T>
set <int> FindCsByFilter(const unordered_map <int, CS>& cs, Filter<T> f, T param)
{
	set <int> res;
	int i = 0;
	for (auto& [id, station] : cs)
	{
		if (f(station, param))
			res.insert(i);
		i++;
	}

	return res;
}
void Edit_cs(unordered_map <int, CS>& cs, set <int>& id_filter) {

	if ((id_filter.size()) == 0)
	{
		cout << " You do not have a stations for a given filter " << endl;
		return;
	}
	cout << "You have " + to_string(id_filter.size()) + " cs.";
	cout << "Id filter: ";
	for (auto i : id_filter)
		cout << i << " ";
	cout << "Enter number of stations to edit.";
	int number_of_cs = GetCorrect(0, int(id_filter.size()));
	set<int>id_selected;
	for (int i = 1; i <= number_of_cs; i++)
	{
		cout << "Enter id cs: ";
		int id = GetCorrect(0, *max_element(id_filter.begin(), id_filter.end()));
		if (id_filter.find(id) != id_filter.end())
		{
			id_selected.insert(id);
		}
		else {
			cout << "There is no such id in the filter. Please try again " << endl;
			i = i - 1;
		}
	}
	for (int id : id_selected)
	{
		CS& station = cs[id];
		station.workshops_work = GetCorrect(0,station.workshops);
	}

}

void Delete_cs(unordered_map <int, CS>& cs, set <int>& id_filter) {
	if ((id_filter.size()) == 0)
	{
		cout << " You do not have a stations for a given filter " << endl;
		return;
	}
	cout << "You have " + to_string(id_filter.size()) + " cs.";
	cout << "Id filter: ";
	for (auto i : id_filter)
		cout << i << " ";
	cout << "Enter number of stations to delete. ";
	int number_of_cs = GetCorrect(0, int(id_filter.size()));
	set<int>id_selected;
	for (int i = 1; i <= number_of_cs; i++)
	{
		cout << "Enter id cs: ";
		int id = GetCorrect(0, *max_element(id_filter.begin(), id_filter.end()));
		if (id_filter.find(id) != id_filter.end())
		{
			id_selected.insert(id);
			id_filter.erase(id);
		}
		else {
			cout << "There is no such id in the filter. Please try again" << endl;
			i = i - 1;
		}
	}
	for (int id : id_selected)
	{
		cs.erase(id);
	}

}

int Edit_or_delet_cs(unordered_map <int, CS>& cs, set <int>& id_filter) {
	while (true)
	{
		cout << "You have " + to_string(id_filter.size()) + " stations." << endl;
		cout << "\nSelect menu item:"
			<< "\n1. CS edit"
			<< "\n2. CS delet"
			<< "\n3. Exit" << endl;
		int vibor = -1;
		vibor = GetCorrect(1, 3);
		switch (vibor)
		{
		case 1:
		{
			Edit_cs(cs, id_filter);
			break;
		}
		case 2:
		{
			Delete_cs(cs, id_filter);
			break;
		}
		case 3:
		{
			cout << "3. Exit" << endl;
			return false;
		}
		}
	}
}
int Filter_cs(unordered_map <int, CS>& cs) {

	cout << "\nSelect menu item:"
		<< "\n1. CS filter by name"
		<< "\n2. CS filter by % of unused workshops"
		<< "\n3. Select all"
		<< "\n4. Exit" << endl;
	int vibor = -1;
	vibor = GetCorrect(1, 4);
	switch (vibor)
	{
	case 1:
	{
		cout << "Enter name for filter: ";
		string name = "Unknown";
		cin >> name;
		set <int>id_filter;
		id_filter = FindCsByFilter(cs, CheckByName, name);
		Edit_or_delet_cs(cs, id_filter);
		break;
	}
	case 2:
	{
		cout << "Enter procent unusing shops: ";
		int k = GetCorrect(0, 100);
		cout << "\nSelect menu item:"
			<< "\n1. > "
			<< "\n2. = "
			<< "\n3. < " << endl;
		set <int>id_filter;
		int vibor = GetCorrect(1, 3);
		switch (vibor)
			{
			case 1: {
				
				id_filter = FindCsByFilter(cs, CheckByWorshopsMore, k);
				Edit_or_delet_cs(cs, id_filter);
				break;
			}
			case 2: {
				id_filter = FindCsByFilter(cs, CheckByWorshopsEqual, k);
				Edit_or_delet_cs(cs, id_filter);
				break;
			}
			case 3: {
				id_filter = FindCsByFilter(cs, CheckByWorshopsLess, k);
				Edit_or_delet_cs(cs, id_filter);
				break;
			}
		}
		break;
	}
	case 3:
	{
		set <int> id_filter;
		for (auto& [id, station] : cs) {
			id_filter.insert(id);
		}
		Edit_or_delet_cs(cs, id_filter);
		break;
	}
	case 4:
	{
		cout << "4. Exit" << endl;
		return false;
	}
	}
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

void Read_from_file_cs(unordered_map <int, CS>& s)
{
	s.clear();
	ifstream fin;
	string filename;
	cout << "Enter name of file for station: ";
	cin >> filename;
	fin.open(filename + ".txt");
	if (fin)
	{
		string name_of_cs = "none";
		bool kp = 0;
		while (getline(fin, name_of_cs))
		{
			if (name_of_cs == "Station:")
			{
				CS cs;
				fin >> cs.MaxIDCS;
				fin >> cs.idcs;
				fin.clear();
				fin.ignore(1000, '\n');
				getline(fin, cs.name_cs);
				fin >> cs.workshops;
				fin >> cs.workshops_work;
				fin >> cs.effect;
				s.insert({ cs.idcs ,cs });
				kp = true;
			}
		}
		if (!kp)
		{
			cout << "No information about cs." << endl;
		}
		else
			return OutputCs(s);
	}
	fin.close();
}
