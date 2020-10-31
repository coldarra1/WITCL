#include <iostream>
#include <string>

using namespace std;

class CEmployee
{
private:
	int ID;
	string Name;
	string Sex;
	int Age;
	double Salary;

public:
	CEmployee();
	~CEmployee();
	int GetID();
	void SetID(int ID);
	string GetName();
	void SetName(string Name);
	string GetSex();
	void SetSex(string Sex);
	int GetAge();
	void SetAge(int Age);
	double GetSalary();
	void SetSalary(double Salary);
	void Display();
};

CEmployee::CEmployee()
{
	cout<<"Constructor CEmployee::CEmployee()!"<<endl;

	ID=0;
	Name="No Name";
	Sex="Female";
	Age=0;
	Salary=0.0;
}

CEmployee::~CEmployee()
{
	cout<<"Destructor CEmployee::~CEmployee()!"<<endl;
}

int CEmployee::GetID()
{
	return ID;
}

void CEmployee::SetID(int ID)
{
	if(ID>0)
	{
		this->ID=ID;
	}
}

string CEmployee::GetName()
{
	return Name;
}

void CEmployee::SetName(string Name)
{
	this->Name=Name;
}

string CEmployee::GetSex()
{
	return Sex;
}

void CEmployee::SetSex(string Sex)
{
	if((Sex=="Female")||(Sex=="Male"))
	{
		this->Sex=Sex;
	}
}

int CEmployee::GetAge()
{
	return Age;
}

void CEmployee::SetAge(int Age)
{
	if((Age>=18)&&(Age<=60))
	{
		this->Age=Age;
	}
}

double CEmployee::GetSalary()
{
	return Salary;
}

void CEmployee::SetSalary(double Salary)
{
	if(Salary>0.0)
	{
		this->Salary=Salary;
	}
}

void CEmployee::Display()
{
	cout<<"--------------------"<<endl;
	cout<<"Employee ID: "<<ID<<endl;
	cout<<"Name       : "<<Name<<endl;
	cout<<"Sex        : "<<Sex<<endl;
	cout<<"Age        : "<<Age<<endl;
	cout<<"Salary     : "<<Salary<<endl;
	cout<<"===================="<<endl;
}

int main()
{
	CEmployee Employees[4];

	Employees[0].SetID(1);
	Employees[0].SetName("Zhang San");
	Employees[0].SetSex("Male");
	Employees[0].SetAge(25);
	Employees[0].SetSalary(5000.0);

	Employees[1].SetID(2);
	Employees[1].SetName("Li Si");
	Employees[1].SetSex("Female");
	Employees[1].SetAge(25);
	Employees[1].SetSalary(5000.0);

	Employees[2].SetID(3);
	Employees[2].SetName("Wang Wu");
	Employees[2].SetSex("Male");
	Employees[2].SetAge(30);
	Employees[2].SetSalary(8000.0);

	for(int i=0;i<4;i++)
	{
		Employees[i].Display();
	}

	cout<<"--------------------"<<endl;

	for(int j=0;j<4;j++)
	{
		if(Employees[j].GetID()!=0)
		{
			cout<<"Employee ID: "<<Employees[j].GetID()<<'\t';
			cout<<"Name: "<<Employees[j].GetName()<<'\t';
			cout<<"Sex: "<<Employees[j].GetSex()<<'\t';
			cout<<"Age: "<<Employees[j].GetAge()<<'\t';
			cout<<"Salary: "<<Employees[j].GetSalary()<<endl;
		}
		else
		{
			cout<<"Invalid Employee Information!"<<endl;
		}

		cout<<"--------------------"<<endl;
	}

	return 0;
}

