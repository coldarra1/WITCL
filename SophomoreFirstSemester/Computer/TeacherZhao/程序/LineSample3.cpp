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
	CPoint(const CPoint& Point);
	~CPoint();

	const CPoint& operator =(const CPoint& Point);
	int GetX();
	int GetY();
};

CPoint::CPoint() : x(0),y(0)
{
	cout<<"ctor CPoint::CPoint()!"<<endl;
}

CPoint::CPoint(int x1,int y1) : x(x1),y(y1)
{
	cout<<"ctor CPoint::CPoint(int x1,int y1)!"<<endl;
}

CPoint::CPoint(const CPoint& Point) : x(Point.x),y(Point.y)
{
	cout<<"cctor CPoint::CPoint(const CPoint& Point)!"<<endl;
}

CPoint::~CPoint()
{
	cout<<"dtor CPoint::~CPoint()!"<<endl;
}

const CPoint& CPoint::operator =(const CPoint& Point)
{
	cout<<"const CPoint& CPoint::operator =(const CPoint& Point)!"<<endl;

	if(this!=&Point)
	{
		x=Point.x;
		y=Point.y;
	}

	return *this;
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
	CLine(const CLine& Line);
	~CLine();

	const CLine& operator =(const CLine& Line);
	double GetLength();
};

CLine::CLine()
{
	cout<<"ctor CLine::CLine()!"<<endl;
}

CLine::CLine(int x1,int y1,int x2,int y2) : Start(x1,y1),End(x2,y2)
{
	cout<<"ctor CLine::CLine(int x1,int y1,int x2,int y2)!"<<endl;
}

CLine::CLine(const CLine& Line) : Start(Line.Start),End(Line.End)
{
	cout<<"cctor CLine::CLine(const CLine& Line)!"<<endl;
}

/*
CLine::CLine(const CLine& Line)
{
	cout<<"cctor CLine::CLine(const CLine& Line)!"<<endl;

	Start=Line.Start;
	End=Line.End;
}
*/

CLine::~CLine()
{
	cout<<"dtor CLine::~CLine()!"<<endl;
}

const CLine& CLine::operator =(const CLine& Line)
{
	cout<<"const CLine& CLine::operator =(const CLine& Line)!"<<endl;

	if(this!=&Line)
	{
		this->Start=Line.Start;
		this->End=Line.End;
	}

	return *this;
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

	CLine Line3(Line2);

	cout<<Line3.GetLength()<<endl;

	cout<<"----------"<<endl;

	CLine Line4;

	Line4=Line2;
	//Line4.operator =(Line2);

	cout<<Line4.GetLength()<<endl;

	cout<<"----------"<<endl;

	CLine Line5=CLine(Line2);

	cout<<Line5.GetLength()<<endl;

	cout<<"----------"<<endl;

	CLine Line6;
	
	Line6=CLine(Line2);

	cout<<Line6.GetLength()<<endl;

	cout<<"----------"<<endl;

	return 0;
}

