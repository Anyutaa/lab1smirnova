#pragma once
#include <string>
#include <unordered_map>
using namespace std;

class Truba
{
private:
	
	double lenght = 0;
	int diametr = 0;
	int idpipe = 0;
	static int MaxIDTruba;
	
public:
	string name_truba = "None";
	bool repair = false;
	Truba();
	int get_idp() { return idpipe; };
	friend istream& operator >> (istream& in, Truba& tr);
	friend ostream& operator << (ostream& out, const Truba& tr);
	friend void Add_pipe(unordered_map < int, Truba >& pipes);
	friend void DataRecordingPipe(ofstream& fout, const Truba& pipe);
	friend void Read_from_file_pipe(unordered_map <int, Truba>& p);
	//friend void Edit_pipe(unordered_map <int, Truba>& p, vector <int>& id_filter);
	friend int Filter_pipe(unordered_map <int, Truba>& p);
};

void OutputPipe(unordered_map <int, Truba>& p);
