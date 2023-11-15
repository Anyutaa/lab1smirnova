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

void Edit_cs(unordered_map <int, CS>& cs, vector <int>& id_filter) {
	if ((id_filter.size()) != 0) {
		cout << "Enter number of cs to edit.  You have" + to_string(id_filter.size()) + " cs.";
		int number_of_cs = GetCorrect(0, int(id_filter.size()));
		for (int i = 1; i <= number_of_cs; i++)
		{
			cout << "Enter id pipe: ";
			int id = GetCorrect(0, int(*max_element(id_filter.begin(), id_filter.end())));
			if (find(id_filter.begin(), id_filter.end(), id) != id_filter.end()) {
				CS& station = cs[id];
				station.workshops_work = GetCorrect(0, station.workshops);
			}
		}
	}
	else
		cout << " You do not have a cs for a given filter" << endl;
}

void Delete_cs(unordered_map <int, CS>& cs, vector <int>& id_filter) {
	if ((id_filter.size()) != 0) {
		cout << "Enter number of cs to delete. You have " + to_string(id_filter.size()) + " cs.";
		int number_of_cs = GetCorrect(0, int(id_filter.size()));
		for (int i = 1; i <= number_of_cs; i++)
		{
			cout << "Enter id station: ";
			int id = GetCorrect(0, int(*max_element(id_filter.begin(), id_filter.end())));
			if (find(id_filter.begin(), id_filter.end(), id) != id_filter.end()) {
				cs.erase(id);
				vector<int>::iterator itr = std::find(id_filter.begin(), id_filter.end(), id);
				id_filter.erase(itr);
				
			}
		}
	}
	else
		cout << " You do not have a cs for a given filter" << endl;
}

int Edit_or_delet_cs(unordered_map <int, CS>& cs, vector <int>& id_filter) {
	while (true)
	{
		cout << "You have " + to_string(id_filter.size()) + " cs." << endl;
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
int Filter_cs(unordered_map <int, CS>& cs)
{

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
		string cs_name;
		cout << "Enter name: ";
		cin.ignore();
		getline(cin, cs_name);
		vector <int> id_filter;
		for (auto& cs1 : cs) {
			CS& station = cs1.second;
			if (station.name_cs.find(cs_name) != string::npos) {
				id_filter.push_back(station.idcs);
			}
		}
		Edit_or_delet_cs(cs, id_filter);
		break;
	}
	case 2:
	{
		int cs_procent;
		cout << "Enter procent unusing shops: ";
		cs_procent=GetCorrect(0,100);
		vector <int> id_filter;
		cout << "\nSelect menu item:"
			<< "\n1. > "
			<< "\n2. = "
			<< "\n3. < " << endl;
		int vibor = GetCorrect(1, 3);
		switch (vibor)
		{
		case 1: {
			for (auto& cs2 : cs) {
				CS& station2 = cs2.second;
				if (((station2.workshops - station2.workshops_work) * 100 / station2.workshops) > cs_procent) {
					id_filter.push_back(station2.idcs);
				}
			}
			Edit_or_delet_cs(cs, id_filter);
			break;
		}
		case 2: {
			for (auto& cs2 : cs) {
				CS& station2 = cs2.second;
				if (((station2.workshops - station2.workshops_work) * 100 / station2.workshops) == cs_procent) {
					id_filter.push_back(station2.idcs);
				}

			}
			Edit_or_delet_cs(cs, id_filter);
			break;
		}
		case 3: {
			for (auto& cs2 : cs) {
				CS& station2 = cs2.second;
				if (((station2.workshops - station2.workshops_work) * 100 / station2.workshops) < cs_procent) {
					id_filter.push_back(station2.idcs);
				}
			}
			Edit_or_delet_cs(cs, id_filter);
			break;
		}
		}
		break;
	}
	case 3:
	{
		vector <int> id_filter;
		for (auto& cs3 : cs) {
			id_filter.push_back(cs3.first);
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
//void Writing_to_file_cs(unordered_map <int, CS>& s)
//{
//	string filename;
//	cin >> filename;
//	ofstream fout;
//	fout.open((filename + ".txt"), ios::app);
//	if ((s.size()) == 0)
//	{
//		cout << "No information about pipe " << endl;
//		return;
//	}
//	cout << "Add information about pipe " << endl;
//	for (const auto& x : s)
//		DataRecordingCS(fout, x.second);
//
//	fout.close();
//}
//void Read_from_file_cs(unordered_map <int, CS>& s)
//{
//	ifstream fin("lab_smirnova.txt");
//	if (fin)
//	{
//		string name_of_cs = "none";
//		bool ks = 0;
//		while (getline(fin, name_of_cs))
//		{
//			if (name_of_cs == "Station: ")
//			{
//				CS cs;
//				int m = 0;
//				fin >> m;
//				fin >> cs.MaxIDCS;
//				fin >> cs.idcs;
//				getline(fin, cs.name_cs);
//				fin >> cs.workshops;
//				fin >> cs.workshops_work;
//				fin >> cs.effect;
//				s.insert({ m,cs });
//				ks = true;
//			}
//		}
//		if (!ks)
//		{
//			cout << "No information about station." << endl;
//		}
//		else
//			return OutputCs(s);
//	}
//	fin.close();
////}
//
