#include <iostream>

using namespace std;

class CBaseClass
{
private:
	int a;
	int b;

public:
	CBaseClass() : a(0),b(0) {}
	CBaseClass(int a1,int b1) : a(a1),b(b1) {}

	void Display();
};

void CBaseClass::Display()
{
	cout<<"a="<<a<<" b="<<b<<endl;
}

class CMyClass : public CBaseClass
{
private:
	int c;

public:
	CMyClass() : c(0) {}
	CMyClass(int a1,int b1,int c1) : CBaseClass(a1,b1),c(c1) {}

	void Display2();
};

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

	return 0;
}

