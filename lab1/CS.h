#pragma once
#include <string>
#include <unordered_map>
using namespace std;

class CS
{
private:
	
	char effect = 'A';
	int idcs = 0;
	static int MaxIDCS;
	
public:
	string name_cs = "None";
	int workshops = 0;
	int workshops_work = 0;
	CS();
	int get_idc() { return idcs; };
	friend istream& operator >> (istream& in, CS& cs);
	friend ostream& operator << (ostream& in, const CS& cs);
	friend class Truba_CS;
	friend void DataRecordingCS(ofstream& fout, const CS& cs);
};
