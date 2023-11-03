#include <iostream> 
#include <fstream>
#include <string>
#include <unordered_map>
#include "Truba.h"
#include "CS.h"
#include "utils.h"

using namespace std;

//struct Truba
//{
//	string name_truba = "None";
//	double lenght = 0;
//	int diametr = 0;   
//	bool repair = false;
//};

//struct CS
//{
//	string name_cs = "None";
//	int workshops = 0;
//	int workshops_work = 0;
//	char effect = 'A';
//};

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
void OutputCs( unordered_map <int, CS>& s)
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

//Truba& SelectTruba(unordered_map <int, Truba>& p)
//{
//		cout << "Enter index for pipe: ";
//		unsigned int index = GetCorrect(0u, unsigned int(p.size() - 1));
//		return p[index];
//}
//
//CS& SelectCS(unordered_map <int, CS>& s)
//{
//		cout << "Enter index for station: ";
//		unsigned int index = GetCorrect(0u, unsigned int(s.size() - 1));
//		return s[index];
//}


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
		fout << "Pipe: \n" << x.first << " " << x.second << endl;

	fout.close(); 
}

void Writing_to_file_cs( unordered_map <int, CS>& s)
{
	ofstream fout("lab_smirnova.txt",ios::app);
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
				p.insert({ m,pipe});
				kp =true;
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

void Read_from_file_cs( unordered_map <int, CS>& s)
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
				s.insert({m,cs});
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

int main()
{
	unordered_map < int, Truba > pipes;
	unordered_map < int, CS > stations;
	while (true)
	{
		cout << "\nSelect menu item:"
			<< "\n1. Add pipe"
			<< "\n2. Add CS"
			<< "\n3. View all objects"
			<< "\n4. Edit pipe"
			<< "\n5. Edit KS"
			<< "\n6. Save"
			<< "\n7. Dowload"
			<< "\n8. Exit" 
			<< "\nChoose action ";
		int vibor = -1;
		vibor = GetCorrect(1,8);
		switch (vibor)
		{
		case 1:
		{
			Truba pipe;
			cout << "1. Add pipe" << endl;
			cin >> pipe;
			pipes.insert({ pipe.get_idp(),pipe});
			break;
		}
		case 2:
		{
			CS station;
			cout << "2. Add Cs" << endl;
			cin >> station;
			stations.insert({ station.get_idc(),station});
			break;
		}
		case 3:
		{
			cout << "3. View all objects" << endl;
			OutputPipe(pipes);
			OutputCs( stations);
			break;
		}
		case 4:
		{
			if ((pipes.size()) != 0) {
				cout << "4. Edit pipe" << endl;
				int mid = (pipes.size()) - 1;
				int id = 0;
				cout << "Enter id pipe: ";
				id = GetCorrect(0,mid);
				Truba pipe;
				cout << "Entry the pipe state ";
				pipe = pipes[id];
				pipe.repair= GetCorrect(0, 1);
				pipes.erase(id);
				pipes.insert({ id,pipe});
			}
			else
				cout << " You do not have a pipe" << endl;
			break;
		}
		case 5:
		{
			if ((stations.size()) != 0) {
				cout << "5. Edit Cs" << endl;
				int mid = (pipes.size()) - 1;
				int id = 0;
				cout << "Enter id station: " ;
				id = GetCorrect(0, mid);
				CS cs;
				cout << "Entry the number of workshops ";
				cs = stations[id];
				cs.workshops_work = GetCorrect(0, cs.workshops);
				stations.erase(id);
				stations.insert({ id,cs});
				
			}
			else
				cout << " You do not have a compressor station " << endl;
			break;
		}
		case 6:
		{
			cout << "6. Save" << endl;
			Writing_to_file_pipe(pipes);
			Writing_to_file_cs(stations);
			break;
		}
		case 7:
		{
			cout << "7. Download" << endl;
			Read_from_file_pipe(pipes);
			Read_from_file_cs( stations);
			break;
		}
		case 8:
		{
			cout << "8. Exit" << endl;
			return false;
		}
		default:
		{
			cout << "Entry a number from  1 to 8 " << endl;
			break;
		}
		}
	}
	return 0;
}