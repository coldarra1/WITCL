#include <iostream>

using namespace std;

class CBaseClass
{
private:
	int a;
	int b;

public:
	CBaseClass();
	CBaseClass(int a1,int b1);
	~CBaseClass();

	void Display();
};

CBaseClass::CBaseClass() : a(0),b(0)
{
	cout<<"Constructor CBaseClass::CBaseClass()!"<<endl;
}

CBaseClass::CBaseClass(int a1,int b1) : a(a1),b(b1)
{
	cout<<"Constructor CBaseClass::CBaseClass(int a1,int b1)!"<<endl;
}

CBaseClass::~CBaseClass()
{
	cout<<"Destructor CBaseClass::~CBaseClass()!"<<endl;
}

void CBaseClass::Display()
{
	cout<<"a="<<a<<" b="<<b<<endl;
}

class CMyClass : public CBaseClass
{
private:
	int c;

public:
	CMyClass();
	CMyClass(int a1,int b1,int c1);
	~CMyClass();

	void Display2();
};

CMyClass::CMyClass() : c(0)
{
	cout<<"Constructor CMyClass::CMyClass()!"<<endl;
}

CMyClass::CMyClass(int a1,int b1,int c1) : CBaseClass(a1,b1),c(c1)
{
	cout<<"Constructor CMyClass::CMyClass(int a1,int b1,int c1)!"<<endl;
}

CMyClass::~CMyClass()
{
	cout<<"Destructor CMyClass::~CMyClass()!"<<endl;
}

void CMyClass::Display2()
{
	cout<<"c="<<c<<endl;
}

int main()
{
	CBaseClass Obj1;
	CBaseClass Obj2(1,2);

	Obj1.Display();
	Obj2.Display();

	cout<<"----------"<<endl;

	CMyClass Obj3;
	CMyClass Obj4(3,4,5);

	Obj3.Display();
	Obj3.Display2();

	Obj4.Display();
	Obj4.Display2();

	cout<<"----------"<<endl;

	return 0;
}

