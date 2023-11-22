#include <iostream> 
#include <fstream>
#include <string>
#include <unordered_map>
#include "Truba.h"
#include "CS.h"
#include "Truba_cs.h"
#include "utils.h"
#include <chrono>
#include <format>
#include <set>
#include <algorithm>

using namespace std;
using namespace chrono;


int main()
{
	Truba_CS gts;
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
			<< "\n7. Download"
			<< "\n8. Exit"
			<< "\nChoose action ";
		int vibor = -1;
		vibor = GetCorrect(1,8);
		switch (vibor)
		{
		case 1:
		{
			gts.Add_pipe(pipes);
			break;
		}
		case 2:
		{
			gts.Add_cs(stations);
			break;
		}
		case 3:
		{
			cout << "3. View all objects" << endl;
			gts.OutputPipe(pipes);
			gts.OutputCs(stations);
			break;
		}
		case 4:
		{
			cout << "4. Filter for pipes" << endl;
			gts.Filter_pipe(pipes);

			break;
		}
		case 5:
		{
			cout << "5. Filter for cs" << endl;
			gts.Filter_cs(stations);
			break;
		}
		case 6:
		{
			cout << "6. Save" << endl;
			gts.Writing_to_file_pipe_cs(pipes,stations);
			break;
		}
		case 7:
		{
			cout << "7. Download" << endl;
			gts.Read_from_file_pipe(pipes);
			gts.Read_from_file_cs( stations);
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