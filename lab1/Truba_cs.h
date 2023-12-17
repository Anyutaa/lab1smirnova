#pragma once
#include <string>
#include "Truba.h"
#include "CS.h"
#include <unordered_map>
using namespace std;

class Truba_CS
{
public:
	int id_entry;
	int id_pipe;
	int id_outlet;

	void Add_pipe(unordered_map < int, Truba >& pipes);
	void Add_cs(unordered_map < int, CS >& stations);
	void OutputPipe(unordered_map <int, Truba>& p);
	void OutputCs(unordered_map <int, CS>& s);
	bool Filter_pipe(unordered_map <int, Truba>& p, unordered_map <int, CS>& cs, vector<Truba_CS>& connection);
	bool Filter_cs(unordered_map <int, Truba>& p,unordered_map <int, CS>& cs, vector<Truba_CS>& connection);
	void Read_from_file_pipe(unordered_map <int, Truba>& p);
	void Read_from_file_cs(unordered_map <int, CS>& s);
	void Writing_to_file_pipe_cs(unordered_map <int, Truba>& p, unordered_map <int, CS>& s);
	void Connection(unordered_map <int, Truba>& p, unordered_map <int, CS>& s, vector<Truba_CS>& connection);
	int Add_newpipe_connect(unordered_map<int, Truba>& pipe, int diameter);
	void All_connections(vector<Truba_CS>& connection);
};
