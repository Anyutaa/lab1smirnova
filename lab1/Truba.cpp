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
	cout << "You have " + to_string(id_filter.size()) + " pipes.";
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
	}

}

void Delete_pipe(unordered_map <int, Truba>& p, set <int>& id_filter) {
	if ((id_filter.size()) == 0)
	{
		cout << " You do not have a pipes for a given filter " << endl;
		return;
	}
	cout << "You have " + to_string(id_filter.size()) + " pipes.";
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
int Filter_pipe(unordered_map <int, Truba>& p) {

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

istream& operator >> (istream& in, Truba& tr)
{
	cout << "Enter name truba:";
	cin.ignore();
	getline(cin, tr.name_truba);
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

void Read_from_file_pipe(unordered_map <int, Truba>& p)
{
	p.clear();
	ifstream fin;
	string filename;
	cout << "Enter name of file for pipe: ";
	cin >> filename;
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