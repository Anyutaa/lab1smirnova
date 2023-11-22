#include "Truba.h"
#include "CS.h"
#include "Truba_cs.h"
#include <iostream> 
#include <fstream>
#include <string>
#include "utils.h"
#include <unordered_map>
#include <set>

void Truba_CS::Add_pipe(unordered_map < int, Truba >& pipes) {
	Truba pipe;
	cout << "1. Add pipe" << endl;
	cin >> pipe;
	pipes.insert({ pipe.get_idp(),pipe });

}
void Truba_CS::Add_cs(unordered_map < int, CS >& stations) {
	CS station;
	cout << "2. Add Cs" << endl;
	cin >> station;
	stations.insert({ station.get_idc(),station });

}
void Truba_CS::OutputPipe(unordered_map <int, Truba>& p)
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

void Truba_CS::OutputCs(unordered_map <int, CS>& s)
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

template<typename T>
using Filter = bool(*)(const Truba& tr, T param);

bool CheckByName(const Truba& tr, string param)
{
	return tr.name_truba.find(param) != string::npos;
}
bool CheckByRepair(const Truba& tr, bool param)
{
	return tr.repair == param;
}

template<typename T>
set <int> FindPipesByFilter(const unordered_map <int, Truba>& p, Filter<T> f, T param)
{
	set <int> res;
	int i = 0;
	for (auto& [id, pipe] : p)
	{
		if (f(pipe, param))
			res.insert(i);
		i++;

	}

	return res;
}
void Edit_pipe(unordered_map <int, Truba>& p, set <int>& id_filter) {

	if ((id_filter.size()) == 0)
	{
		cout << " You do not have a pipes for a given filter " << endl;
		return;
	}
	cout << "You have " + to_string(id_filter.size()) + " pipes on the filter.";
	cout << "Id filter: ";
	for (auto i : id_filter)
		cout << i << " ";
	cout << "Enter number of pipes to edit.";
	int number_of_pipes = GetCorrect(0, int(id_filter.size()));
	set<int>id_selected;
	for (int i = 1; i <= number_of_pipes; i++)
	{
		cout << "Enter id pipe: ";
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
		Truba& pipe = p[id];
		pipe.repair = !pipe.repair;
		cout << "You edit " << id << " pipe." << endl;
	}

}

void Delete_pipe(unordered_map <int, Truba>& p, set <int>& id_filter) {
	if ((id_filter.size()) == 0)
	{
		cout << " You do not have a pipes for a given filter " << endl;
		return;
	}
	cout << "You have " + to_string(id_filter.size()) + " pipes on the filter.";
	cout << "Id filter: ";
	for (auto i : id_filter)
		cout << i << " ";
	cout << "Enter number of pipes to delete. ";
	int number_of_pipes = GetCorrect(0, int(id_filter.size()));
	set<int>id_selected;
	for (int i = 1; i <= number_of_pipes; i++)
	{
		cout << "Enter id pipe: ";
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
		p.erase(id);
		cout << "You delet " << id << " pipe." << endl;
	}

}

int Edit_or_delet(unordered_map <int, Truba>& p, set <int>& id_filter) {
	while (true)
	{
		cout << "You have " + to_string(id_filter.size()) + " pipes." << endl;
		cout << "\nSelect menu item:"
			<< "\n1. Pipe edit"
			<< "\n2. Pipe delet"
			<< "\n3. Exit" << endl;
		int vibor = -1;
		vibor = GetCorrect(1, 3);
		switch (vibor)
		{
		case 1:
		{
			Edit_pipe(p, id_filter);
			break;
		}
		case 2:
		{
			Delete_pipe(p, id_filter);
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
int Truba_CS::Filter_pipe(unordered_map <int, Truba>& p) {

	cout << "\nSelect menu item:"
		<< "\n1. Pipe filter by name"
		<< "\n2. Pipe filter by under repair"
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
		cerr << name << endl;
		set <int>id_filter;
		id_filter = FindPipesByFilter(p, CheckByName, name);
		Edit_or_delet(p, id_filter);
		break;
	}
	case 2:
	{
		cout << "Enter repair (0,1) for filter" << endl;
		bool k = GetCorrect(0, 1);
		set<int>id_filter;
		id_filter = FindPipesByFilter(p, CheckByRepair, k);
		Edit_or_delet(p, id_filter);
		break;
	}
	case 3:
	{
		set <int> id_filter;
		for (auto& [id, pipe] : p) {
			id_filter.insert(id);
		}
		Edit_or_delet(p, id_filter);
		break;
	}
	case 4:
	{
		cout << "4. Exit" << endl;
		return false;
	}
	}
}

template<typename T>
using  Filter1 = bool(*)(const CS& cs, T param);

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
set <int> FindCsByFilter(const unordered_map <int, CS>& cs, Filter1<T> f, T param)
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
	cout << "You have " + to_string(id_filter.size()) + " cs on the filter.";
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
		station.workshops_work = GetCorrect(0, station.workshops);
		cout << "You edit " << id << " cs." << endl;
	}

}

void Delete_cs(unordered_map <int, CS>& cs, set <int>& id_filter) {
	if ((id_filter.size()) == 0)
	{
		cout << " You do not have a stations for a given filter " << endl;
		return;
	}
	cout << "You have " + to_string(id_filter.size()) + " cs on the filter.";
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
		cout << "You delet " << id << " cs." << endl;
	}

}

int Edit_or_delet_cs(unordered_map <int, CS>& cs, set <int>& id_filter) {
	while (true)
	{
		cout << "You have " + to_string(id_filter.size()) + " stations on the filter." << endl;
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
int Truba_CS::Filter_cs(unordered_map <int, CS>& cs) {

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
		cerr << name << endl;
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


void Truba_CS::Writing_to_file_pipe_cs(unordered_map <int, Truba>& p, unordered_map <int, CS>& s)
{
	if ((p.size()) == 0 && (s.size()) == 0)
	{
		cout << "No information about pipe and cs " << endl;
		return;
	}
	else {
		cout << "Enter file name: ";
		string filename;
		cin >> filename;
		cerr << filename << endl;
		ofstream fout;
		fout.open((filename + ".txt"), ios::trunc);

		if (fout.is_open())
		{

			if ((p.size()) == 0)
			{
				cout << "You do not have pipe" << endl;
			}
			else {
				for (const auto& x : p)
					DataRecordingPipe(fout, x.second);
				cout << "Add information about pipe " << endl;
			}
			if ((s.size()) == 0)
			{
				cout << "You do not have compressor station" << endl;
			}
			else {
				for (const auto& x : s)
					DataRecordingCS(fout, x.second);
				cout << "Add information about station " << endl;
			}

			fout.close();
		}
	}
}
void Truba_CS::Read_from_file_pipe(unordered_map <int, Truba>& p)
{
	p.clear();
	ifstream fin;
	string filename;
	cout << "Enter name of file for pipe: ";
	cin >> filename;
	cerr << filename << endl;
	fin.open(filename + ".txt");
	if (fin)
	{
		string name_of_truba = "none";
		bool kp = 0;
		while (getline(fin, name_of_truba))
		{
			if (name_of_truba == "Pipe:")
			{
				Truba pipe;
				fin >> pipe.MaxIDTruba;
				fin >> pipe.idpipe;
				fin.clear();
				fin.ignore(1000, '\n');
				getline(fin, pipe.name_truba);
				fin >> pipe.lenght;
				fin >> pipe.diametr;
				fin >> pipe.repair;
				p.insert({ pipe.idpipe ,pipe });
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

void Truba_CS::Read_from_file_cs(unordered_map <int, CS>& s)
{
	s.clear();
	ifstream fin;
	string filename;
	cout << "Enter name of file for station: ";
	cin >> filename;
	cerr << filename << endl;
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