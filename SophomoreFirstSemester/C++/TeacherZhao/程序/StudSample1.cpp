#include <iostream>
#include <string.h>

using namespace std;

struct STUDENT
{
	int StudNo;
	char StudName[33];
};

void DisplayStudent(STUDENT *pStud)
{
	cout<<"Student No  : "<<pStud->StudNo<<endl;
	cout<<"Student Name: "<<pStud->StudName<<endl;
	cout<<"----------"<<endl;
}

int main()
{
	STUDENT Stud1,Stud2,Stud3;

	Stud1.StudNo=1;
	strcpy(Stud1.StudName,"Zhang San");
	Stud2.StudNo=2;
	strcpy(Stud2.StudName,"Li Si");
	Stud3.StudNo=3;
	strcpy(Stud3.StudName,"Wang Wu");

	DisplayStudent(&Stud1);
	DisplayStudent(&Stud2);
	DisplayStudent(&Stud3);

	return 0;
}

