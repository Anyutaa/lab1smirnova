#pragma once
#include <iostream> 
using namespace std;

#define INPUT_LINE(in, str) getline(in>>ws, str); \
						cerr << str << endl

#define PRINT_PARAM(out, x) out<< #x << "=" << x << endl

class redirect_output_wrapper
{
	std::ostream& stream;
	std::streambuf* const old_buf;
public:
	redirect_output_wrapper(ostream& src)
		:old_buf(src.rdbuf()), stream(src)
	{
	}

	~redirect_output_wrapper() {
		stream.rdbuf(old_buf);
	}
	void redirect(ostream& dest)
	{
		stream.rdbuf(dest.rdbuf());
	}
};

template <typename T>
T GetCorrect(T min, T max)
{
	T x;
	while ((cin >> x).fail() || cin.peek() != '\n' || x<min || x>max)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Type number (" << min << "-" << max << "):";
	}
	cerr << x << endl;
	return x;
}