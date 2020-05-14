#include <iostream>
#include <string>

using namespace std;

class CStudent
{
public:
	int StudNo;
	string StudName;

	void Display();
};

void CStudent::Display()
{
	cout<<"Student No  : "<<StudNo<<endl;
	cout<<"Student Name: "<<StudName<<endl;
	cout<<"----------"<<endl;
}

int main()
{
	CStudent Stud[3];
	CStudent *pStud;
	int i;

	Stud[0].StudNo=1;
	Stud[0].StudName="Zhang San";
	Stud[1].StudNo=2;
	Stud[1].StudName="Li Si";
	Stud[2].StudNo=3;
	Stud[2].StudName="Wang Wu";

	for(i=0;i<3;i++)
	{
		pStud=&Stud[i];

		pStud->Display();
	}

	return 0;
}

