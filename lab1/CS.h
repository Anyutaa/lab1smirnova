#pragma once
#include <string>;
using namespace std;
class CS
{
public:
	static int MaxIDCS;
	int idcs;
	CS();
	string name_cs = "None";
	int workshops = 0;
	int workshops_work = 0;
	char effect = 'A';
	friend istream& operator >> (istream& in, CS& cs);
	friend ostream& operator << (ostream& in, CS& cs);
	int get_idc() { return idcs; };
};

