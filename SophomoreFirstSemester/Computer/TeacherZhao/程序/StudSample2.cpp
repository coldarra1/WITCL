#include <iostream>
#include <string.h>

using namespace std;

struct STUDENT
{
	int StudNo;
	char StudName[33];

	void Display()
	{
		cout<<"Student No  : "<<StudNo<<endl;
		cout<<"Student Name: "<<StudName<<endl;
		cout<<"----------"<<endl;
	}
};

int main()
{
	STUDENT Stud1,Stud2,Stud3;

	Stud1.StudNo=1;
	strcpy(Stud1.StudName,"Zhang San");
	Stud2.StudNo=2;
	strcpy(Stud2.StudName,"Li Si");
	Stud3.StudNo=3;
	strcpy(Stud3.StudName,"Wang Wu");

	Stud1.Display();
	Stud2.Display();
	Stud3.Display();

	return 0;
}

