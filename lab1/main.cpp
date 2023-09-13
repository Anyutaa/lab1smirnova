#include <iostream> 
#include <vector>
using namespace std;

struct Truba 
{
	string otmetka;
	double dlina;
	int diametr;
	bool remont;
};

struct KC {
	string nazvanKC;
	int kolvotsekh;
	int tsekhvrabote;
	char effect;
};
int main()
{
	vector <Truba> truboprovod;
	size_t n = 0;
	cin >> n;
	truboprovod.resize(n);

	vector <KC> KCgroup;
	size_t m = 0;
	cin >> m;
	KCgroup.resize(m);

	return 0;
}