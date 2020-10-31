#include <iostream>

using namespace std;

#define COUNT 10

int main()
{
	int *a;
	int i,j;

	a=new int[COUNT];

	if(a==NULL)
	{
		return 1;
	}

	for(i=0;i<COUNT;i++)
	{
		cin>>a[i];
	}

	for(j=0;j<COUNT;j++)
	{
		cout<<a[j]<<" ";
	}
	cout<<endl;

	delete[] a;

	return 0;
}

