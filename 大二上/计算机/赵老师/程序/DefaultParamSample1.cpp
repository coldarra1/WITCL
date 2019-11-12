#include <iostream>

using namespace std;

void Print(int a,int b=0);

int main()
{
	Print(1);

	cout<<"----------"<<endl;

	Print(2,3);

	return 0;
}

void Print(int a,int b)
{
	cout<<a<<endl;

	if(b!=0)
	{
		cout<<b<<endl;
	}
}

