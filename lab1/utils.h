#pragma once
#include <iostream> 
using namespace std;


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
	return x;
}