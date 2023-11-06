#pragma once
#include <string>
#include <unordered_map>
using namespace std;

class CS
{
private:
	string name_cs = "None";
	int workshops = 0;
	int workshops_work = 0;
	char effect = 'A';
	int idcs = 0;
public:
	unordered_map < int, CS > stations;
	static int MaxIDCS;
	CS();
	int get_idc() { return idcs; };
	friend istream& operator >> (istream& in, CS& cs);
	friend ostream& operator << (ostream& in, const CS& cs);
	friend void Add_cs(unordered_map < int, CS >& stations);
	friend void OutputCs(unordered_map <int, CS>& s);
	friend void Writing_to_file_cs(unordered_map <int, CS>& s);
	friend void Read_from_file_cs(unordered_map <int, CS>& s);
	
};

