#include <iostream>

using namespace std;

class CBaseClass
{
protected:
	int a;
	int b;

public:
	CBaseClass();
	CBaseClass(int a1,int b1);
	virtual ~CBaseClass();

	virtual void Display();
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

	void Display();
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

void CMyClass::Display()
{
	cout<<"a="<<a<<" b="<<b<<" c="<<c<<endl;
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
	Obj4.Display();

	cout<<"----------"<<endl;

	CBaseClass *pObj1;
	CMyClass *pObj2;

	pObj1=new CBaseClass(6,7);
	pObj2=new CMyClass(8,9,10);

	pObj1->Display();
	pObj2->Display();

	delete pObj1;
	delete pObj2;

	cout<<"----------"<<endl;

	CBaseClass *pObj3;

	pObj3=new CMyClass(11,12,13);

	pObj3->Display();

	delete pObj3;

	cout<<"----------"<<endl;

	return 0;
}

