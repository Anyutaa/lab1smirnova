#include <iostream> 
#include <fstream>
#include <string>
using namespace std;

struct Truba 
{
	string name_truba = "None";
	double lenght = 0;
	int diametr = 0;
	bool repair = false ;
};

struct CS
{
	string name_cs = "None";
	int workshops = 0;
	int workshops_work = 0;
	char effect = 'A';
};

int Enter_vibor()
{
	cout << "\nSelect: ";
	int vibor = -1;
	cin >> vibor;
	while (cin.fail() || cin.peek() != '\n')
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Try again \n";
		cout << "Select: ";
		cin >> vibor;
	}
	return vibor;
}

double proverka_doub(double& doub)
{
	cin >> doub;
	while (cin.fail() || cin.peek() != '\n' || doub <= 0)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Try again \n";
		cout << "Enter double ";
		cin >> doub;
	}
	return doub;
}

int proverka_int(int& inter)
{
	cin >> inter;
	while (cin.fail() || cin.peek() != '\n' || inter<=0)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Try again \n";
		cout << "Enter integer ";
		cin >> inter;
	}
	return inter;
}

bool proverka_bool(bool& bolli)
{
	cin >> bolli;
	while (cin.fail() || cin.peek() != '\n')
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Try again \n";
		cout << "Enter bool ";
		cin >> bolli;
	}
	return bolli;

}

char proverka_char(char& chari)
{
	cin >> chari;
	while (cin.fail() || cin.peek() != '\n' || chari <'A' || chari>'D')
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Enter a value from A to D \n";
		cin >> chari;
	}
	return chari;
}

Truba enter_truba()
{
	Truba tr;
	cout << "Enter name truba:";
	cin.ignore();
	getline(cin, tr.name_truba);
	cout << "Enter lenght:";
	proverka_doub(tr.lenght);
	cout << "Enter diametr:";
	proverka_int(tr.diametr) ;
	cout << "Enter repair:";
	proverka_bool( tr.repair);
	return tr;

};

CS enter_CS()
{
	CS cs;
	cout << "Enter name CS:";
	cin.ignore();
	getline(cin, cs.name_cs);
	cout << "Enter workshops:";
	proverka_int (cs.workshops);
	cout << "Enter workshops in work:";
	proverka_int (cs.workshops_work);
	while (cs.workshops < cs.workshops_work)
	{
		cout << "Enter a smaller value" << endl;
		proverka_int(cs.workshops_work);
	}
	cout << "Enter effect:";
	proverka_char(cs.effect);
	return cs;
};

void Print_truba(const Truba& tr)
{
	if ((tr.name_truba) != "None") {
		cout << "Pipe:" << endl;
		cout << "Enter name truba:" << tr.name_truba
			<< "\nEnter lenght:" << tr.lenght
			<< "\nEnter diametr:" << tr.diametr
			<< "\nEnter repair : " << tr.repair << endl;
	}
	else
		cout<< "You do not have pipe" << endl;
};

void Print_CS(const CS& cs)
{
	if ((cs.name_cs) != "None") {
		cout << "Station:" << endl;
		cout << "Enter name Cs:" << cs.name_cs
			<< "\nEnter workshops:" << cs.workshops
			<< "\nEnter workshops in work:" << cs.workshops_work
			<< "\nEnter effect: " << cs.effect << endl;
	}
	else
		cout << "You do not have compressor station" << endl;
};

void Writing_to_file(Truba& pipe, CS& station)
{
	ofstream fout("lab_smirnova.txt");
	if ((pipe.name_truba) != "None") {
		cout << "Add information about pipe "<<endl;
		fout << "Pipe" << endl;
		fout << pipe.name_truba << endl;
		fout << pipe.lenght << endl;
		fout << pipe.diametr << endl;
		fout << pipe.repair << endl;
	}
	else
		cout << "No information about pipe " << endl;

	if ((station.name_cs) != "None") {
		cout << "Add information about station " << endl;
		fout << "Station" << endl;
		fout << station.name_cs << endl;
		fout << station.workshops << endl;
		fout << station.workshops_work << endl;
		fout << station.effect << endl;
	}
	else
		cout << "No information about station " << endl;
	fout.close();
}

void Read_from_file(Truba& pipe, CS& station)
{
	ifstream fin("lab_smirnova.txt");
	if (fin)
	{
		string name_of_cs_or_truba = "no";
		int p = 0;
		int s = 0;
		while (getline(fin, name_of_cs_or_truba))
		{
			if (name_of_cs_or_truba == "Pipe")
			{
				cout << "Data received from file about pipe:" << endl;
				cout << "\nPipe" << endl;
				getline(fin, pipe.name_truba);
				cout << "Pipe name: " << pipe.name_truba << endl;
				fin >> pipe.lenght;
				cout << "Pipe length: " << pipe.lenght << endl;
				fin >> pipe.diametr;
				cout << "Pipe diameter: " << pipe.diametr << endl;
				fin >> pipe.repair;
				cout << "The pipe attribute: " << pipe.repair << endl;
				p += 1;
			}
			if (name_of_cs_or_truba == "Compressor station")
			{
				cout << "Data received from file about Cs:" << endl;
				cout << "\nCompressor station" << endl;
				getline(fin, station.name_cs);
				cout << "Cs name: " << station.name_cs << endl;
				fin >> station.workshops;
				cout << "Number of workshops of the Cs: " << station.workshops << endl;
				fin >> station.workshops_work;
				cout << "Number of workshops in operation of the Cs: " << station.workshops_work << endl;
				fin >> station.effect;
				cout << "CS efficiency: " << station.effect << endl;
				s += 1;
			}
		}

		if (p == 0)
		{
			cout << "No information about pipe." << endl;
		}
		if (s == 0)
		{
			cout << "No information about station." << endl;
		}
	}
	fin.close();
}

int main()
{
	Truba pipe;
	CS station;
	while (true)
	{
	cout << "\nSelect menu item:" 
		<<"\n1. Add pipe"
		<<"\n2. Add CS"
		<<"\n3. View all objects"
		<<"\n4. Edit pipe"
		<<"\n5. Edit KS"
		<<"\n6. Save"
		<<"\n7. Dowload"
		<<"\n8. Exit" << endl;
		switch (Enter_vibor())
		{
		case 1:
		{
			if ((pipe.name_truba) == "None") {
				cout << "1. Add pipe" << endl;
				pipe = enter_truba();
			}
			else
				cout<< "You have already entered the pipe" << endl;
			break;
		}
		case 2:
		{
			if ((station.name_cs) == "None") {
				cout << "2. Add Cs" << endl;
				station  = enter_CS();
			}
			else
				cout << "You have already entered the station" << endl;
			break;
		}
		case 3:
		{
			cout << "3. View all objects" << endl;
			Print_truba(pipe);
			Print_CS(station);
			break;
		}
		case 4:
		{
			if ((pipe.name_truba) != "None") {
				cout << "4. Edit pipe" << endl;
				cout << "Entry the pipe state ";
				proverka_bool(pipe.repair);
			}
			else
				cout<<" You do not have a pipe" << endl;
			break;
		}
		case 5:
		{
			if ((station.name_cs) != "None") {
				cout << "5. Edit Cs" << endl;
				cout << "Entry the number of workshops ";
				proverka_int(station.workshops_work);
				while (station.workshops < station.workshops_work)
				{
					cout << "Enter a smaller value " << endl;
					proverka_int(station.workshops_work);
				}
			}
			else
				cout << " You do not have a compressor station " << endl;
			break;
		}
		case 6:
		{
			cout << "6. Save" << endl;
			Writing_to_file(pipe, station);
			break;
		}
		case 7:
		{
			cout << "7. Dowload" << endl;
			Read_from_file(pipe, station);
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