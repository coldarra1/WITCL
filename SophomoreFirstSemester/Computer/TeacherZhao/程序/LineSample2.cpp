#include <iostream>
#include <cmath>

using namespace std;

class CPoint
{
private:
	int x;
	int y;

public:
	CPoint();
	CPoint(int x1,int y1);
	~CPoint();

	int GetX();
	int GetY();

	friend class CLine;
};

CPoint::CPoint()
{
	cout<<"ctor CPoint::CPoint()!"<<endl;

	x=0;
	y=0;
}

CPoint::CPoint(int x1,int y1)
{
	cout<<"ctor CPoint::CPoint(int x1,int y1)!"<<endl;

	x=x1;
	y=y1;
}

CPoint::~CPoint()
{
	cout<<"dtor CPoint::~CPoint()!"<<endl;
}

int CPoint::GetX()
{
	return x;
}

int CPoint::GetY()
{
	return y;
}

class CLine
{
private:
	CPoint Start;
	CPoint End;

public:
	CLine();
	CLine(int x1,int y1,int x2,int y2);
	~CLine();

	double GetLength();
};

CLine::CLine()
{
	cout<<"ctor CLine::CLine()!"<<endl;
}

CLine::CLine(int x1,int y1,int x2,int y2)
{
	cout<<"ctor CLine::CLine(int x1,int y1,int x2,int y2)!"<<endl;

	Start.x=x1;
	Start.y=y1;

	End.x=x2;
	End.y=y2;
}

CLine::~CLine()
{
	cout<<"dtor CLine::~CLine()!"<<endl;
}

double CLine::GetLength()
{
	double len;

	len=sqrt(pow((double)End.GetX()-(double)Start.GetX(),2.0)+pow((double)End.GetY()-(double)Start.GetY(),2.0));

	return len;
}

int main()
{
	CLine Line1;

	cout<<Line1.GetLength()<<endl;

	cout<<"----------"<<endl;

	CLine Line2(0,0,4,3);

	cout<<Line2.GetLength()<<endl;

	cout<<"----------"<<endl;

	return 0;
}

