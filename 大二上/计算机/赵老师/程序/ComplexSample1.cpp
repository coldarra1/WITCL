#include <iostream>

using namespace std;

class CComplex
{
private:
	double real;
	double imag;

public:
	CComplex();
	CComplex(double real,double imag);
	CComplex(const CComplex &z);
	~CComplex();

	double GetReal() const;
	double GetImag() const;
	void Display();
};

CComplex::CComplex()
{
	cout<<"Constructor CComplex::CComplex()!"<<endl;

	real=0.0;
	imag=0.0;
}

CComplex::CComplex(double real,double imag)
{
	cout<<"Constructor CComplex::CComplex(double real,double imag)!"<<endl;

	this->real=real;
	this->imag=imag;
}

CComplex::CComplex(const CComplex &z)
{
	cout<<"Copy constructor CComplex::CComplex(const CComplex &z)!"<<endl;

	real=z.real;
	imag=z.imag;
}

CComplex::~CComplex()
{
	cout<<"Destructor CComplex::~CComplex()!"<<endl;
}

double CComplex::GetReal() const
{
	return real;
}

double CComplex::GetImag() const
{
	return imag;
}

void CComplex::Display()
{
	cout<<real<<'+'<<imag<<'i'<<endl;
}

CComplex Global_z;

void DisplayComplex(const CComplex &z)
{
	cout<<z.GetReal()<<'+'<<z.GetImag()<<'i'<<endl;
}

int main()
{
	cout<<"----------"<<endl;

	CComplex z1;

	z1.Display();

	cout<<"----------"<<endl;

	CComplex *pz1;

	pz1=new CComplex;

	pz1->Display();

	delete pz1;

	cout<<"----------"<<endl;

	CComplex z2(3.0,4.0);

	z2.Display();

	cout<<"----------"<<endl;

	CComplex *pz2;

	pz2=new CComplex(3.0,4.0);

	pz2->Display();

	delete pz2;

	cout<<"----------"<<endl;

	CComplex z3(6.0,8.0);

	DisplayComplex(z3);

	cout<<"----------"<<endl;

	CComplex z4(z3);

	z4.Display();

	cout<<"----------"<<endl;

	return 0;
}

