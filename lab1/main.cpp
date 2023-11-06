#include <iostream> 
#include <fstream>
#include <string>
#include <unordered_map>
#include "Truba.h"
#include "CS.h"
#include "utils.h"
using namespace std;


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
		/*case 4:
		{
			if ((pipes.size()) != 0) {
				cout << "Enter number of pipes to edit: ";
				int number_of_pipes = 0;
				cin >> number_of_pipes;
				int i;
				int mid = (pipes.size()) - 1;
				for (i = 1; i <= number_of_pipes; i++)
				{
					int id = 0;
					cout << "Enter id pipe: ";
					id = GetCorrect(0, mid);
					cout << "Entry the pipe state ";
					Truba& pipe = pipes[id];
					pipe.repair = GetCorrect(0, 1);
					
				}
			}
			else
				cout << " You do not have a pipe" << endl;
			break;
		}
		case 5:
		{

			if ((stations.size()) != 0) {
				cout << "Enter number of cs to edit: ";
				int number_of_cs = 0;
				cin >> number_of_cs;
				int i;
				int mid = (stations.size()) - 1;
				for (i = 1; i <= number_of_cs; i++)
				{
					int id = 0;
					cout << "Enter id station: ";
					id = GetCorrect(0, mid);
					cout << "Entry the number of workshops ";
					CS& cs = stations[id];
					cs.workshops_work = GetCorrect(0, cs.workshops);
			
				}
			}
			else
				cout << " You do not have a compressor station" << endl;
			break;*/

			/*if ((stations.size()) != 0) {
				cout << "5. Edit Cs" << endl;
				int mid = (pipes.size()) - 1;
				int id = 0;
				cout << "Enter id station: " ;
				id = GetCorrect(0, mid);
				cout << "Entry the number of workshops ";
				CS& cs = stations[id];
				cs.workshops_work = GetCorrect(0, cs.workshops);
				
			}
			else
				cout << " You do not have a compressor station " << endl;
			break;*/
		/*}*/
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