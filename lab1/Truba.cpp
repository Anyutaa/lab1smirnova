#include "Truba.h"
#include <iostream> 
#include <fstream>
#include <string>
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

void Edit_pipe(unordered_map <int, Truba>& p, vector <int>& id_filter){
		if ((id_filter.size()) != 0) {
				cout << "Enter number of pipes to edit.  You have"+to_string(id_filter.size())+" pipes.";
				int number_of_pipes = GetCorrect(0, int(id_filter.size()));
				for (int i = 1; i <= number_of_pipes; i++)
				{
					cout << "Enter id pipe: ";
					int id = GetCorrect(0, int(*max_element(id_filter.begin(), id_filter.end())));
					if (find(id_filter.begin(), id_filter.end(), id) != id_filter.end()) {
						Truba& pipe = p[id];
						pipe.repair = !pipe.repair;
					}
				}
			}
			else
				cout << " You do not have a pipes for a given filter" << endl;
}

void Delete_pipe(unordered_map <int, Truba>& p, vector <int>& id_filter){
	if ((id_filter.size()) != 0) {
		cout << "Enter number of pipes to delete. You have " + to_string(id_filter.size()) + " pipes.";
		int number_of_pipes = GetCorrect(0, int(id_filter.size()));
		for (int i = 1; i <= number_of_pipes; i++)
		{
			cout << "Enter id pipe: ";
			int id = GetCorrect(0, int(*max_element(id_filter.begin(), id_filter.end())));
			if (find(id_filter.begin(), id_filter.end(), id) != id_filter.end()){
				p.erase(id);
				vector<int>::iterator itr = std::find(id_filter.begin(), id_filter.end(), id);
				id_filter.erase(itr);
			}
		}
	}
	else
		cout << " You do not have a pipes for a given filter" << endl;
}

int Edit_or_delet(unordered_map <int, Truba>& p, vector <int>& id_filter) {
	while (true)
	{ 
		cout << "You have " + to_string(id_filter.size()) + " pipes."<<endl;
		cout << "\nSelect menu item:"
			<< "\n1. Pipe edit"
			<< "\n2. Pipe delet"
			<< "\n3. Exit"<<endl;
		int vibor = -1;
		vibor = GetCorrect(1, 3);
		switch (vibor)
		{
		case 1:
		{
			Edit_pipe(p,id_filter);
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
int Filter_pipe(unordered_map <int, Truba>& p)
{

	cout << "\nSelect menu item:"
		<< "\n1. Pipe filter by name"
		<< "\n2. Pipe filter by under repair"
		<< "\n3. Select all"
		<<"\n4. Exit"<<endl;
	int vibor = -1;
	vibor = GetCorrect(1, 4);
	switch (vibor)
	{
	case 1:
	{
		string pipe_name;
		cout << "Enter name: ";
		cin.ignore();
		getline(cin, pipe_name);
		vector <int> id_filter;
		for ( auto& pipe1 : p) {
			Truba& truba1 = pipe1.second;
			if (truba1.name_truba.find(pipe_name) != string::npos) {
				id_filter.push_back(truba1.idpipe);
			}
		}
		Edit_or_delet(p,id_filter);
		break;
	}
	case 2:
	{
		bool pipe_repair;
		cout << "Enter under repair: ";
		cin >> pipe_repair;
		vector <int> id_filter;
		for (auto& pipe2 : p) {
			Truba& truba2 = pipe2.second;
			if (truba2.repair == pipe_repair) {
				id_filter.push_back(truba2.idpipe);
			}
		}
		Edit_or_delet(p, id_filter);
		break;
	}
	case 3:
	{
		vector <int> id_filter;
		for (auto& pipe3 : p) {
			//Truba& truba3 = pipe3.second;
			id_filter.push_back(pipe3.first);
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