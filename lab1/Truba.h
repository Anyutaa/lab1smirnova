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
public:
	unordered_map < int, Truba > pipes;
	static int MaxIDTruba;
	Truba();
	friend istream& operator >> (istream& in, Truba& tr);
	friend ostream& operator << (ostream& out, const Truba& tr);
	int get_idp() { return idpipe; };
	friend void Add_pipe(unordered_map < int,  Truba >& pipes);
	friend void OutputPipe(unordered_map <int, Truba>& p);
	friend void Writing_to_file_pipe(unordered_map <int, Truba>& p);
	friend void Read_from_file_pipe(unordered_map <int, Truba>& p);
};

