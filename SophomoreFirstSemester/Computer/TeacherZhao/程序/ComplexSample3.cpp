#include <iostream>

using namespace std;

class CComplex;
ostream& operator <<(ostream& os,const CComplex& z);

class CComplex
{
private:
	double real;
	double imag;

public:
	CComplex();
	CComplex(double real,double imag);
	CComplex(const CComplex& z);
	~CComplex();

	double GetReal() const;
	double GetImag() const;
	void Display();
	const CComplex& operator =(const CComplex& z);
	const CComplex& operator +=(const CComplex& z);
	const CComplex& operator -=(const CComplex& z);
	const CComplex operator +(const CComplex& z) const;
	const CComplex operator -(const CComplex& z) const;

	friend ostream& operator <<(ostream& os,const CComplex& z);
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

CComplex::CComplex(const CComplex& z)
{
	cout<<"Copy constructor CComplex::CComplex(const CComplex& z)!"<<endl;

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

const CComplex& CComplex::operator =(const CComplex& z)
{
	cout<<"const CComplex& CComplex::operator =(const CComplex& z)!"<<endl;

	real=z.GetReal();
	imag=z.GetImag();

	return *this;
}

const CComplex& CComplex::operator +=(const CComplex& z)
{
	real+=z.GetReal();
	imag+=z.GetImag();

	return *this;
}

const CComplex& CComplex::operator -=(const CComplex& z)
{
	real-=z.GetReal();
	imag-=z.GetImag();

	return *this;
}

const CComplex CComplex::operator +(const CComplex& z) const
{
	CComplex temp;

	temp.real=this->real+z.GetReal();
	temp.imag=this->imag+z.GetImag();

	return temp;
}

const CComplex CComplex::operator -(const CComplex& z) const
{
	CComplex temp;

	temp.real=this->real-z.GetReal();
	temp.imag=this->imag-z.GetImag();

	return temp;
}

ostream& operator <<(ostream& os,const CComplex& z)
{
	cout<<z.real<<'+'<<z.imag<<'i';

	return os;
}

int main()
{
	CComplex z1(1,1),z2(3,3),z3(2,2);
	CComplex z4(1,1),z5(3,3);
	CComplex z6;
	CComplex z7(2,2);
	CComplex z8;

	cout<<"----------"<<endl;

	//z1.operator +=(z2);
	z1+=z2;
	z1.Display();

	cout<<"----------"<<endl;

	//z1.operator -=(z3);
	z1-=z2;
	z1.Display();

	cout<<"----------"<<endl;

	//z6.operator =(z4.operator +=(z5));
	z6=z4+=z5;
	z4.Display();
	z6.Display();

	cout<<"----------"<<endl;

	//z8.operator =(z4.operator -=(z7));
	z8=z4-=z7;
	z4.Display();
	z8.Display();

	cout<<"=========="<<endl;

	CComplex z9(z1),z10(z1);

	z9.Display();
	z10.Display();

	cout<<"----------"<<endl;

	CComplex z11,z12;

	//z12.operator =(z11.operator =(z1));
	z12=z11=z1;

	z11.Display();
	z12.Display();

	cout<<"----------"<<endl;

	CComplex z13,z14;

	//z13.operator =(z1.operator +(z2));
	z13=z1+z2;
	//z14.operator =(z2.operator -(z3));
	z14=z2-z3;

	//z13.Display();
	//z14.Display();

	cout<<z13<<endl;
	cout<<z14<<endl;

	cout<<"----------"<<endl;

	return 0;
}

