#include <iostream>

using namespace std;

class CShape
{
protected:
	int x1,y1,x2,y2;

public:
	CShape(int x1,int y1,int x2,int y2);
	virtual void Draw();
};

CShape::CShape(int x1,int y1,int x2,int y2)
{
	this->x1=x1;
	this->y1=y1;
	this->x2=x2;
	this->y2=y2;
}

void CShape::Draw()
{
}

class CLine : public CShape
{
public:
	CLine(int x1,int y1,int x2,int y2) : CShape(x1,y1,x2,y2) {}
	void Draw();
};

void CLine::Draw()
{
	cout<<"Line ("<<x1<<","<<y1<<")-("<<x2<<","<<y2<<")"<<endl;
}

class CRectangle : public CShape
{
public:
	CRectangle(int x1,int y1,int x2,int y2) : CShape(x1,y1,x2,y2) {}
	void Draw();
};

void CRectangle::Draw()
{
	cout<<"Rectangle ("<<x1<<","<<y1<<")-("<<x2<<","<<y2<<")"<<endl;
}

class CEllipse : public CShape
{
public:
	CEllipse(int x1,int y1,int x2,int y2) : CShape(x1,y1,x2,y2) {}
	void Draw();
};

void CEllipse::Draw()
{
	cout<<"Ellipse ("<<x1<<","<<y1<<")-("<<x2<<","<<y2<<")"<<endl;
}

int main()
{
	CShape *pShapes[3];

	pShapes[0]=new CLine(100,100,199,199);
	pShapes[1]=new CRectangle(300,100,399,199);
	pShapes[2]=new CEllipse(500,100,599,199);

	for(int i=0;i<3;i++)
	{
		pShapes[i]->Draw();
	}

	return 0;
}

