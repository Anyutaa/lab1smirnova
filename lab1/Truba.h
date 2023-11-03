#pragma once
#include <string>;
using namespace std;

class Truba
{
	
public:
	static int MaxIDTruba;
	int idpipe=0;
	Truba();
	string name_truba = "None";
	double lenght = 0;
	int diametr = 0;
	bool repair = false;
	friend istream& operator >> (istream& in, Truba& tr);
	friend ostream& operator << (ostream& out, Truba& tr);
	int get_idp() { return idpipe; };
	/*friend void Writing_to_file_pipe(unordered_map <int, Truba>& p);*/
};

