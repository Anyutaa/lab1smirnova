#include "Truba.h"
#include "CS.h"
#include "Truba_cs.h"
#include <iostream> 
#include <fstream>
#include <string>
#include "utils.h"
#include <unordered_map>
#include <set>
#include <queue>
#include <stack>

void Truba_CS::Add_pipe(unordered_map < int, Truba >& pipes) {
	Truba pipe;
	cout << "1. Add pipe" << endl;
	cin >> pipe;
	pipes.insert({ pipe.get_idp(),pipe });

}
void Truba_CS::Add_cs(unordered_map < int, CS >& stations) {
	CS station;
	cout << "2. Add Cs" << endl;
	cin >> station;
	stations.insert({ station.get_idc(),station });

}
void Truba_CS::OutputPipe(unordered_map <int, Truba>& p)
{
	if ((p.size()) == 0)
	{
		cout << "You do not have pipe" << endl;
	}
	else
		for (auto x : p)
			cout << x.first << " " <<
			x.second << endl;
}

void Truba_CS::OutputCs(unordered_map <int, CS>& s)
{
	if ((s.size()) == 0)
	{
		cout << "You do not have compressor station" << endl;
	}
	else
		for (auto x : s)
			cout << x.first << " " <<
			x.second << endl;

}

template<typename T>
using Filter = bool(*)(const Truba& tr, T param);

bool CheckByName(const Truba& tr, string param)
{
	return tr.name_truba.find(param) != string::npos;
}
bool CheckByRepair(const Truba& tr, bool param)
{
	return tr.repair == param;
}

template<typename T>
set <int> FindPipesByFilter(const unordered_map <int, Truba>& p, Filter<T> f, T param)
{
	set <int> res;
	int i = 0;
	for (auto& [id, pipe] : p)
	{
		if (f(pipe, param))
			res.insert(i);
		i++;

	}

	return res;
}
void Edit_pipe(unordered_map <int, Truba>& p, set <int>& id_filter) {

	if ((id_filter.size()) == 0)
	{
		cout << " You do not have a pipes for a given filter " << endl;
		return;
	}
	cout << "You have " + to_string(id_filter.size()) + " pipes on the filter.";
	cout << "Id filter: ";
	for (auto i : id_filter)
		cout << i << " ";
	cout << "Enter number of pipes to edit.";
	int number_of_pipes = GetCorrect(0, int(id_filter.size()));
	set<int>id_selected;
	for (int i = 1; i <= number_of_pipes; i++)
	{
		cout << "Enter id pipe: ";
		int id = GetCorrect(0, *max_element(id_filter.begin(), id_filter.end()));
		if (id_filter.find(id) != id_filter.end())
		{
			id_selected.insert(id);
		}
		else {
			cout << "There is no such id in the filter. Please try again " << endl;
			i = i - 1;
		}
	}
	for (int id : id_selected)
	{
		Truba& pipe = p[id];
		pipe.repair = !pipe.repair;
		cout << "You edit " << id << " pipe." << endl;
	}

}

void Delete_pipe(unordered_map <int, Truba>& p, unordered_map <int, CS>& cs, set <int>& id_filter, vector<Truba_CS>& connection) {
	if ((id_filter.size()) == 0)
	{
		cout << " You do not have a pipes for a given filter " << endl;
		return;
	}
	cout << "You have " + to_string(id_filter.size()) + " pipes on the filter.";
	cout << "Id filter: ";
	for (auto i : id_filter)
		cout << i << " ";
	cout << "Enter number of pipes to delete. ";
	int number_of_pipes = GetCorrect(0, int(id_filter.size()));
	set<int>id_selected;
	for (int i = 1; i <= number_of_pipes; i++)
	{
		cout << "Enter id pipe: ";
		int id = GetCorrect(0, *max_element(id_filter.begin(), id_filter.end()));
		if (id_filter.find(id) != id_filter.end())
		{
			id_selected.insert(id);
			id_filter.erase(id);
			for (int i = 0; i < connection.size(); i++) {
				Truba_CS Connect;
				Connect = connection[i];
				if (id == Connect.id_pipe) {
					connection.erase(connection.begin() + i);
					cs[Connect.id_entry].id_input -= 1;
					cs[Connect.id_outlet].id_output -= 1;
				}
			}
		}
		else {
			cout << "There is no such id in the filter. Please try again" << endl;
			i = i - 1;
		}
	}
	for (int id : id_selected)
	{
		p.erase(id);
		cout << "You delet " << id << " pipe." << endl;
	}

}

int Edit_or_delet(unordered_map <int, Truba>& p, unordered_map <int, CS>& cs, set <int>& id_filter,  vector<Truba_CS>& connection) {
	while (true)
	{
		cout << "You have " + to_string(id_filter.size()) + " pipes." << endl;
		cout << "\nSelect menu item:"
			<< "\n1. Pipe edit"
			<< "\n2. Pipe delet"
			<< "\n3. Exit" << endl;
		int vibor = -1;
		vibor = GetCorrect(1, 3);
		switch (vibor)
		{
		case 1:
		{
			Edit_pipe(p, id_filter);
			break;
		}
		case 2:
		{
			Delete_pipe(p,cs, id_filter,connection);
			break;
		}
		case 3:
		{
			cout << "3. Exit" << endl;
			return false;
		}
		}
	}
}
bool Truba_CS::Filter_pipe(unordered_map <int, Truba>& p, unordered_map <int, CS>& cs, vector<Truba_CS>& connection) {
	if (p.size()==0){
		cout << "You do not have pipe" << endl;
		return false;
	}
	if (p.size() == 1) {
		cout << "Why do you need a filter for one pipe" << endl;
		return false;
	}
	cout << "\nSelect menu item:"
		<< "\n1. Pipe filter by name"
		<< "\n2. Pipe filter by under repair"
		<< "\n3. Select all"
		<< "\n4. Exit" << endl;
	int vibor = -1;
	vibor = GetCorrect(1, 4);
	switch (vibor)
	{
	case 1:
	{
		cout << "Enter name for filter: ";
		string name = "Unknown";
		cin >> name;
		cerr << name << endl;
		set <int>id_filter;
		id_filter = FindPipesByFilter(p, CheckByName, name);
		if (id_filter.size()) {
			Edit_or_delet(p,cs, id_filter,connection);
		}
		else
			cout << "There are no suitable pipes" << endl;
		break;
	}
	case 2:
	{
		cout << "Enter repair (0,1) for filter" << endl;
		bool k = GetCorrect(0, 1);
		set<int>id_filter;
		id_filter = FindPipesByFilter(p, CheckByRepair, k);
		if (id_filter.size()) {
			Edit_or_delet(p,cs, id_filter,connection);
		}
		else
			cout << "There are no suitable pipes" << endl;
		break;
	}
	case 3:
	{
		set <int> id_filter;
		for (auto& [id, pipe] : p) {
			id_filter.insert(id);
		}
		if (id_filter.size()) {
			Edit_or_delet(p,cs, id_filter,connection);
		}
		else
			cout << "There are no suitable pipes" << endl;
		break;
	}
	case 4:
	{
		cout << "4. Exit" << endl;
		return false;
	}
	}
}

template<typename T>
using  Filter1 = bool(*)(const CS& cs, T param);

bool CheckByName(const CS& cs, string param)
{
	return cs.name_cs.find(param) != string::npos;
}
bool CheckByWorshopsLess(const CS& tr, int param)
{
	return ((tr.workshops - tr.workshops_work) * 100 / tr.workshops) < param;
}
bool CheckByWorshopsEqual(const CS& tr, int param)
{
	return ((tr.workshops - tr.workshops_work) * 100 / tr.workshops) == param;
}
bool CheckByWorshopsMore(const CS& tr, int param)
{
	return ((tr.workshops - tr.workshops_work) * 100 / tr.workshops) > param;
}


template<typename T>
set <int> FindCsByFilter(const unordered_map <int, CS>& cs, Filter1<T> f, T param)
{
	set <int> res;
	int i = 0;
	for (auto& [id, station] : cs)
	{
		if (f(station, param))
			res.insert(i);
		i++;
	}

	return res;
}
void Edit_cs(unordered_map <int, CS>& cs, set <int>& id_filter) {

	if ((id_filter.size()) == 0)
	{
		cout << " You do not have a stations for a given filter " << endl;
		return;
	}
	cout << "You have " + to_string(id_filter.size()) + " cs on the filter.";
	cout << "Id filter: ";
	for (auto i : id_filter)
		cout << i << " ";
	cout << "Enter number of stations to edit.";
	int number_of_cs = GetCorrect(0, int(id_filter.size()));
	set<int>id_selected;
	for (int i = 1; i <= number_of_cs; i++)
	{
		cout << "Enter id cs: ";
		int id = GetCorrect(0, *max_element(id_filter.begin(), id_filter.end()));
		if (id_filter.find(id) != id_filter.end())
		{
			id_selected.insert(id);
		}
		else {
			cout << "There is no such id in the filter. Please try again " << endl;
			i = i - 1;
		}
	}
	for (int id : id_selected)
	{
		CS& station = cs[id];
		cout << "Enter worshops in work: ";
		station.workshops_work = GetCorrect(0, station.workshops);
		cout << "You edit id" << id << " cs." << endl;
	}

}

void Delete_cs(unordered_map <int, Truba>& p,unordered_map <int, CS>& cs, set <int>& id_filter, vector<Truba_CS>& connection) {
	if ((id_filter.size()) == 0)
	{
		cout << " You do not have a stations for a given filter " << endl;
		return;
	}
	cout << "You have " + to_string(id_filter.size()) + " cs on the filter.";
	cout << "Id filter: ";
	for (auto i : id_filter)
		cout << i << " ";
	cout << "Enter number of stations to delete. ";
	int number_of_cs = GetCorrect(0, int(id_filter.size()));
	set<int>id_selected;
	for (int i = 1; i <= number_of_cs; i++)
	{
		cout << "Enter id cs: ";
		int id = GetCorrect(0, *max_element(id_filter.begin(), id_filter.end()));
		if (id_filter.find(id) != id_filter.end())
		{
			id_selected.insert(id);
			id_filter.erase(id);
			for (int i = 0; i < connection.size() ; i++) {
				Truba_CS Connect;
				Connect = connection[i];
				if (id == Connect.id_entry) {
					connection.erase(connection.begin() + i);
					cs[Connect.id_outlet].id_output -= 1;
					p[Connect.id_pipe].free = 1;
				}
				if (id == Connect.id_outlet) {
					connection.erase(connection.begin() + i);
					cs[Connect.id_entry].id_input -= 1;
					p[Connect.id_pipe].free = 1;
				}
			}
		}
		else {
			cout << "There is no such id in the filter. Please try again" << endl;
			i = i - 1;
		}
	}
	for (int id : id_selected)
	{
		cs.erase(id);
		cout << "You delet " << id << " cs." << endl;
	}

}

int Edit_or_delet_cs(unordered_map <int, Truba>& p,unordered_map <int, CS>& cs, set <int>& id_filter, vector<Truba_CS>& connection) {
	while (true)
	{
		for (auto& id : id_filter) {
			cout << cs[id] << endl;
		}
		cout << "You have " + to_string(id_filter.size()) + " stations on the filter." << endl;
		cout << "\nSelect menu item:"
			<< "\n1. CS edit"
			<< "\n2. CS delet"
			<< "\n3. Exit" << endl;
		int vibor = -1;
		vibor = GetCorrect(1, 3);
		switch (vibor)
		{
		case 1:
		{
			Edit_cs(cs, id_filter);
			break;
		}
		case 2:
		{
			Delete_cs(p,cs, id_filter, connection);
			break;
		}
		case 3:
		{
			cout << "3. Exit" << endl;
			return false;
		}
		}
	}
}

bool Truba_CS::Filter_cs(unordered_map <int, Truba>& p,unordered_map <int, CS>& cs, vector<Truba_CS>& connection) {
	if (cs.size() == 0) {
		cout << "You do not have cs" << endl;
		return false;
	}
	if (cs.size() == 1) {
		cout << "Why do you need a filter for one cs" << endl;
		return false;
	}
	
	cout << "\nSelect menu item:"
		<< "\n1. CS filter by name"
		<< "\n2. CS filter by % of unused workshops"
		<< "\n3. Select all"
		<< "\n4. Exit" << endl;
	int vibor = -1;
	vibor = GetCorrect(1, 4);
	switch (vibor)
	{
	case 1:
	{
		cout << "Enter name for filter: ";
		string name = "Unknown";
		cin >> name;
		cerr << name << endl;
		set <int>id_filter;
		id_filter = FindCsByFilter(cs, CheckByName, name);
		if (id_filter.size()) {
			Edit_or_delet_cs(p,cs, id_filter, connection);
		}
		else
			cout<<"There are no suitable cs" << endl;
		break;
	}
	case 2:
	{
		cout << "Enter procent unusing shops: ";
		int k = GetCorrect(0, 100);
		cout << "\nSelect menu item:"
			<< "\n1. > "
			<< "\n2. = "
			<< "\n3. < " << endl;
		set <int>id_filter;
		int vibor = GetCorrect(1, 3);
		switch (vibor)
		{
		case 1: {

			id_filter = FindCsByFilter(cs, CheckByWorshopsMore, k);
			if (id_filter.size()) {
				Edit_or_delet_cs(p,cs, id_filter,connection);
			}
			else
				cout << "There are no suitable cs" << endl;
			
			break;
		}
		case 2: {
			id_filter = FindCsByFilter(cs, CheckByWorshopsEqual, k);
			if (id_filter.size()) {
				Edit_or_delet_cs(p,cs, id_filter,connection);
			}
			else
				cout << "There are no suitable cs" << endl;
			
			break;
		}
		case 3: {
			id_filter = FindCsByFilter(cs, CheckByWorshopsLess, k);
			if (id_filter.size()) {
				Edit_or_delet_cs(p,cs, id_filter,connection);
			}
			else
				cout << "There are no suitable cs" << endl;
			break;
		}
		}
		break;
	}
	case 3:
	{
		set <int> id_filter;
		for (auto& [id, station] : cs) {
			id_filter.insert(id);
		}
		Edit_or_delet_cs(p,cs, id_filter,connection);
		break;
	}
	case 4:
	{
		cout << "4. Exit" << endl;
		return false;
	}
	}
}


void Truba_CS::Writing_to_file_pipe_cs(unordered_map <int, Truba>& p, unordered_map <int, CS>& s)
{
	if ((p.size()) == 0 && (s.size()) == 0)
	{
		cout << "No information about pipe and cs " << endl;
		return;
	}
	else {
		cout << "Enter file name: ";
		string filename;
		cin >> filename;
		cerr << filename << endl;
		ofstream fout;
		fout.open((filename + ".txt"), ios::trunc);

		if (fout.is_open())
		{

			if ((p.size()) == 0)
			{
				cout << "You do not have pipe" << endl;
			}
			else {
				for (const auto& x : p)
					DataRecordingPipe(fout, x.second);
				cout << "Add information about pipe " << endl;
			}
			if ((s.size()) == 0)
			{
				cout << "You do not have compressor station" << endl;
			}
			else {
				for (const auto& x : s)
					DataRecordingCS(fout, x.second);
				cout << "Add information about station " << endl;
			}

			fout.close();
		}
	}
}
void Truba_CS::Read_from_file_pipe(unordered_map <int, Truba>& p)
{
	p.clear();
	ifstream fin;
	string filename;
	cout << "Enter name of file for pipe: ";
	cin >> filename;
	cerr << filename << endl;
	fin.open(filename + ".txt");
	if (fin)
	{
		string name_of_truba = "none";
		bool kp = 0;
		while (getline(fin, name_of_truba))
		{
			if (name_of_truba == "Pipe:")
			{
				Truba pipe;
				fin >> pipe.MaxIDTruba;
				fin >> pipe.idpipe;
				fin.clear();
				fin.ignore(1000, '\n');
				getline(fin, pipe.name_truba);
				fin >> pipe.lenght;
				fin >> pipe.diametr;
				fin >> pipe.repair;
				p.insert({ pipe.idpipe ,pipe });
				kp = true;
			}
		}
		if (!kp)
		{
			cout << "No information about pipe." << endl;
		}
		else
			return OutputPipe(p);
	}
	fin.close();
}

void Truba_CS::Read_from_file_cs(unordered_map <int, CS>& s)
{
	s.clear();
	ifstream fin;
	string filename;
	cout << "Enter name of file for station: ";
	cin >> filename;
	cerr << filename << endl;
	fin.open(filename + ".txt");
	if (fin)
	{
		string name_of_cs = "none";
		bool kp = 0;
		while (getline(fin, name_of_cs))
		{
			if (name_of_cs == "Station:")
			{
				CS cs;
				fin >> cs.MaxIDCS;
				fin >> cs.idcs;
				fin.clear();
				fin.ignore(1000, '\n');
				getline(fin, cs.name_cs);
				fin >> cs.workshops;
				fin >> cs.workshops_work;
				fin >> cs.effect;
				s.insert({ cs.idcs ,cs });
				kp = true;
			}
		}
		if (!kp)
		{
			cout << "No information about cs." << endl;
		}
		else
			return OutputCs(s);
	}
	fin.close();
}

void Truba_CS::Connection(unordered_map <int, Truba>& p, unordered_map <int, CS>& s ,vector<Truba_CS>& connection) {
	if (s.size() == 0) {
		cout << "You do not have stations.";
		return;
	}
	if (p.size() == 0) {
		cout << "You do not have pipes.";
		return;
	}
	int k = 0;
	vector<int>free_cs;
	for (auto& [id, station] : s) {
		if (station.id_input + station.id_output < 2) {
			k += 1;
			free_cs.push_back(id);
		}
	}
	if (k < 2){
		cout << "You do not have free stations";
		return;
	}
	vector<int>free_pipe;
	int n = 0;
	for (auto& [id, pipe] : p) {
		if (pipe.free) {
			n += 1;
			free_pipe.push_back(id);
		}
	}
	if (n < 1) {
		cout << "You do not have free pipe";
		return;
	}
	Truba_CS pipe_connect;
	cout << "Enter the pipe entry ID - CS ";
	cin >> pipe_connect.id_entry;
	if (find(free_cs.begin(),free_cs.end(),pipe_connect.id_entry) == free_cs.end()) {
		while (true) {
			cout << "Enter the value again, no such id.  ";
			cin >> pipe_connect.id_entry;
			if (find(free_cs.begin(), free_cs.end(), pipe_connect.id_entry) != free_cs.end()) {
				s[pipe_connect.id_entry].id_input += 1;
				break;
			}
		}
	}
	else s[pipe_connect.id_entry].id_input += 1;
	cout << "Enter the ID of the pipe outlet ";
	cin >> pipe_connect.id_outlet;
	if (find(free_cs.begin(), free_cs.end(), pipe_connect.id_outlet) == free_cs.end() || pipe_connect.id_outlet == pipe_connect.id_entry) {
		while (true) {
			cout << "Enter the value again, no such id ";
			cin >> pipe_connect.id_outlet;
			if (find(free_cs.begin(), free_cs.end(), pipe_connect.id_outlet) != free_cs.end() && pipe_connect.id_outlet != pipe_connect.id_entry) {
				s[pipe_connect.id_outlet].id_output += 1;
				break;
			}
		}
	}
	else s[pipe_connect.id_outlet].id_output += 1;
	int pipe_diametr;
	int i = 0;
	while (true) {
		cout << "Enter diametr of pipe that you want (500, 700, 1000, 1400):";
		while (true) {
			pipe_diametr = GetCorrect(500, 1400);
			if (pipe_diametr != 500 && pipe_diametr != 700 && pipe_diametr != 1000 && pipe_diametr != 1400)
				cout << "Enter diametr of pipe that you want(500, 700, 1000, 1400): " << endl;
			else
				break;
		}
		for (auto& id_pip : free_pipe) {
			if (p[id_pip].diametr == pipe_diametr) {
				pipe_connect.id_pipe = id_pip;
				i += 1;
				p[id_pip].free = 0;
				break;
			}
		}
		if (i == 1) {
			connection.push_back(pipe_connect);
			cout << "You add connection" << endl;
			break;
		}
		else {
			cout << "You do not have free pipes with diametr that you enter. Let's create. " << endl;
			int available_pipe_id = Add_newpipe_connect(p, pipe_diametr);
			cout << "Created a new pipe with ID " << available_pipe_id << " and diameter " << pipe_diametr << endl;
			pipe_connect.id_pipe = available_pipe_id;
			p[available_pipe_id].free = 0;
			connection.push_back(pipe_connect);
			break;	
		}
	}
	cout << "All connections" << endl;
	for (auto& connect : connection) {
		cout << connect.id_entry << connect.id_pipe << connect.id_outlet << endl;
	}

} 
int Truba_CS::Add_newpipe_connect(unordered_map<int, Truba>& pipe, int diameter) {
	Truba tr1;
	cin >> tr1;
	if (!(tr1.diametr == diameter))
	{
		tr1.diametr = diameter;
		cout << "!!!Your diameter has been changed to the previously entered one: " << diameter << endl;
	}
	int new_pipe_id = tr1.get_idp();
	pipe.insert({ new_pipe_id, tr1 });
	return new_pipe_id;
}
void Truba_CS::All_connections(vector<Truba_CS>& connection) {
	if (connection.size() == 0) {
		cout << "You do not have connections.";
		return;
	}
	cout << "Connections"<< endl;
	for (auto& connect : connection) {
		cout << "Id entry: " << connect.id_entry << " Id pipe: " << connect.id_pipe << " Id outlet: " << connect.id_outlet << endl;
	}
}
//void Truba_CS::Topological_sort(vector<Truba_CS>& graph) {

//}

//void topologicalSortUtil(int v, vector<vector<int>>& adj, vector<bool>& visited, vector<bool>& onStack, stack<int>& s, bool& hasCycle) {
//	visited[v] = true;
//	onStack[v] = true;
//
//	for (int i = 0; i < adj[v].size(); ++i) {
//		int neighbor = adj[v][i];
//		if (!visited[neighbor]) {
//			topologicalSortUtil(neighbor, adj, visited, onStack, s, hasCycle);
//		}
//		else if (onStack[neighbor]) {
//			// ќбнаружен цикл
//			hasCycle = true;
//			return;
//		}
//	}
//
//	onStack[v] = false;
//	s.push(v);
//}
//	
//
//vector<int> Truba_CS::topologicalSort(vector<Truba_CS>& graph) {
//	int numVertices = graph.size();
//
//	// Build adjacency list
//	vector<vector<int>> adj(numVertices, vector<int>());
//
//	for (int i = 0; i < numVertices; ++i) {
//		for (int j = 0; j < numVertices; ++j) {
//			if (i != j && graph[i].id_outlet == graph[j].id_entry) {
//				adj[i].push_back(j);
//			}
//		}
//	}
//
//	// Topological sort using DFS with cycle detection
//	stack<int> s;
//	vector<bool> visited(numVertices, false);
//	vector<bool> onStack(numVertices, false);
//	bool hasCycle = false;
//
//	for (int i = 0; i < numVertices; ++i) {
//		if (!visited[i] && !hasCycle) {
//			topologicalSortUtil(i, adj, visited, onStack, s, hasCycle);
//		}
//	}
//
//	if (hasCycle) {
//		cout << "Graph contains a cycle." << endl;
//		return vector<int>(); // ¬озвращаем пустой вектор, так как топологическую сортировку нельз€ выполнить в графе с циклом.
//	}
//
//	// Collect the result from the stack
//	vector<int> result;
//	while (!s.empty()) {
//		result.push_back(graph[s.top()].id_outlet);
//		result.push_back(graph[s.top()].id_entry);
//		s.pop();
//	}
//
//	return result;
//}
//

bool isCyclicUtil(int v, vector<Truba_CS>& graph, vector<bool>& visited, vector<bool>& recStack) {
	if (!visited[v]) {
		visited[v] = true;
		recStack[v] = true;

		for (auto edge : graph) {
			if (edge.id_entry == v) {
				int i = edge.id_outlet;
				if (!visited[i] && isCyclicUtil(i, graph, visited, recStack))
					return true;
				else if (recStack[i])
					return true;
			}
		}
	}

	recStack[v] = false;
	return false;
}

bool isCyclic(vector<Truba_CS>& graph, int n) {
	vector<bool> visited(n, false);
	vector<bool> recStack(n, false);

	for (int v = 0; v < n; v++) {
		if (isCyclicUtil(v, graph, visited, recStack))
			return true;
	}

	return false;
}

void topologicalSortUtil(int v, vector<Truba_CS>& graph, vector<bool>& visited, stack<int>& stack) {
	visited[v] = true;
	for (auto edge : graph) {
		if (edge.id_entry == v) {
			int i = edge.id_outlet;
			if (!visited[i])
				topologicalSortUtil(i, graph, visited, stack);
		}
	}
	stack.push(v);
}

void Truba_CS::topologicalSort(vector<Truba_CS>& graph) {
	if (graph.size() == 0) {
		cout << "You do not have graph!!!!" << endl;
		return;
	}
	set<int>vertex;
	for (auto& edge : graph) {
		vertex.insert(edge.id_entry);
		vertex.insert(edge.id_outlet);
	}
	int n = size(vertex);
	vector<bool> visited(n, false);
	stack<int> stack;

	for (int v = 0; v < n; v++) {
		if (!visited[v])
			topologicalSortUtil(v, graph, visited, stack);
	}

	vector<int> result;
	while (!stack.empty()) {
		result.push_back(stack.top());
		stack.pop();
	}

	if (isCyclic(graph, n)) {
		cout << "Graph have cycle.\n";
	}
	else {
		cout << "Topologically sorted list of vertices: ";
		for (int v : result) {
			cout << v << " ";
		}
		cout << endl;
	}

	
}


