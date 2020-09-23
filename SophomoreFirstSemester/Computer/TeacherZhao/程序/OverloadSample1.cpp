#include <iostream>

using namespace std;

void Print(int a);
void Print(char *s);

int main()
{
	Print(2);
	Print("Hello, world!");

	return 0;
}

void Print(int a)
{
	cout<<a<<endl;
}

void Print(char *s)
{
	cout<<s<<endl;
}

