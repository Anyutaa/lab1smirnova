//#include "Truba.h"
//#include "CS.h"
//#include "Truba_cs.h"
//#include <iostream> 
//#include <fstream>
//#include <string>
//#include "utils.h"
//
//
//void Writing_to_file_pipe_cs(unordered_map <int, Truba>& p, unordered_map <int, CS>& s)
//{
//	if ((p.size()) == 0 && (s.size()) == 0)
//	{
//		cout << "No information about pipe and cs " << endl;
//		return;
//	}
//	else {
//		string filename;
//		cin >> filename;
//		ofstream fout;
//		fout.open((filename + ".txt"), ios::trunc);
//
//		if (fout.is_open())
//		{
//			fout << p.size() << " " << s.size() << endl;
//			cout << "Add information about pipe " << endl;
//			for (const auto& x : p)
//				DataRecordingPipe(fout, x.second);
//
//			cout << "Add information about station " << endl;
//			for (const auto& x : s)
//				DataRecordingCS(fout, x.second);
//
//			/*for (auto x : p)
//				fout << x.first << " " << x.second << endl;*/
//
//			fout.close();
//		}
//	}
//}
//
////void Read_from_file_pipe(unordered_map <int, Truba>& p)
////{
////	ifstream fin;
////	string filename;
////	cin >> filename;
////	fin.open((filename + ".txt"), ios::in);
////	if (fin)
////	{
////		string name_of_truba = "none";
////		bool kp = 0;
////		while (getline(fin, name_of_truba))
////		{
////			if (name_of_truba == "Pipe: ")
////			{
////				Truba pipe;
////				/*int m = 0;
////				fin >> m;*/
////				fin >> pipe.MaxIDTruba;
////				fin >> pipe.idpipe;
////				/*getline(fin, pipe.name_truba);*/
////				fin >> pipe.name_truba;
////				fin >> pipe.lenght;
////				fin >> pipe.diametr;
////				fin >> pipe.repair;
////				p.insert({ pipe.idpipe ,pipe });
////				kp = true;
////			}
////		}
////		if (!kp)
////		{
////			cout << "No information about pipe." << endl;
////		}
////		else
////			return OutputPipe(p);
////	}
////	fin.close();
////}
//
