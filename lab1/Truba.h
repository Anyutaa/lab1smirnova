#pragma once
#include <string>
#include <unordered_map>
using namespace std;

class Truba
{
private:
	
	int idpipe = 0;
	static int MaxIDTruba;
	
public:
	double lenght = 0;
	int diametr = 0;
	string name_truba = "None";
	bool repair = false;
	bool free = 1;
	Truba();
	int get_idp() { return idpipe; };
	friend istream& operator >> (istream& in, Truba& tr);
	friend ostream& operator << (ostream& out, const Truba& tr);
	friend void DataRecordingPipe(ofstream& fout, const Truba& pipe);
	friend class Truba_CS;
};


