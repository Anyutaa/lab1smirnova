#include <iostream> 
#include <fstream>
#include <string>
#include <unordered_map>
#include "Truba.h"
#include "CS.h"
#include "utils.h"
#include <chrono>
#include <format>

using namespace std;
using namespace chrono;

void Writing_to_file_pipe_cs(unordered_map <int, Truba>& p, unordered_map <int, CS>& s)
{
	if ((p.size()) == 0 && (s.size()) == 0)
	{
		cout << "No information about pipe and cs " << endl;
		return;
	}
	else {
		string filename;
		cin >> filename;
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


int main()
{
	redirect_output_wrapper cerr_out(cerr);
	string time = format("{:%d_%m_%Y %H_%M_%OS}", system_clock::now());
	ofstream logfile("log_" + time);
	if (logfile)
		cerr_out.redirect(logfile);

	unordered_map < int, Truba > pipes;
	unordered_map < int, CS > stations;
	while (true)
	{
		cout << "\nSelect menu item:"
			<< "\n1. Add pipe"
			<< "\n2. Add CS"
			<< "\n3. View all objects"
			<< "\n4. Filter for pipes"
			<< "\n5. Filter for cs"
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
			Add_pipe(pipes);
			break;
		}
		case 2:
		{
			Add_cs(stations);
			break;
		}
		case 3:
		{
			cout << "3. View all objects" << endl;
			OutputPipe(pipes);
			OutputCs(stations);
			break;
		}
		case 4:
		{
			cout << "4. Filter for pipes" << endl;
			Filter_pipe(pipes);
			break;
		}
		case 5:
		{
			cout << "5. Filter for cs" << endl;
			Filter_cs(stations);
			break;
		}
		case 6:
		{
			cout << "6. Save" << endl;
			Writing_to_file_pipe_cs(pipes,stations);
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
		}
	}
	return 0;
}