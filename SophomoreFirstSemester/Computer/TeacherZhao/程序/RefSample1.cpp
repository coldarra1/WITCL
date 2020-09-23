#include <iostream>

using namespace std;

int main()
{
	int a;
	int& r=a;

	a=2;
	cout<<a<<endl;

	r=3;
	cout<<a<<endl;

	return 0;
}

