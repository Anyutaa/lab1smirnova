#pragma once
#include <string>
#include <unordered_map>
using namespace std;

class Truba
{
private:
	string name_truba = "None";
	double lenght = 0;
	int diametr = 0;
	bool repair = false;
	int idpipe = 0;
	friend istream& operator >> (istream& in, Truba& tr);
	friend ostream& operator << (ostream& out, const Truba& tr);
	friend void Add_pipe(unordered_map < int, Truba >& pipes);
	friend void OutputPipe(unordered_map <int, Truba>& p);
	friend void DataRecordingPipe(ofstream& fout, const Truba& pipe);
	friend void Read_from_file_pipe(unordered_map <int, Truba>& p);
	friend void Edit_pipe(unordered_map <int, Truba>& p, vector <int>& id_filter);
	friend int Filter_pipe(unordered_map <int, Truba>& p);
public:
	/*unordered_map < int, Truba > pipes;*/
	static int MaxIDTruba;
	Truba();
	int get_idp() { return idpipe; };
};

