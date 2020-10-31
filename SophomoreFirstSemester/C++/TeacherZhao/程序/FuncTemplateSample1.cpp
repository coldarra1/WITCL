#include <iostream>

using namespace std;

template <typename T>
void Sort(T a[],int n)
{
	T temp;
	int i,j;

	for(i=0;i<n-1;i++)
	{
		for(j=i+1;j<n;j++)
		{
			if(a[i]>a[j])
			{
				temp=a[i];a[i]=a[j];a[j]=temp;
			}
		}
	}
}

int main()
{
	int a1[9]={1,9,2,8,3,7,4,6,5};
	double a2[9]={1.1,1.9,1.2,1.8,1.3,1.7,1.4,1.6,1.5};

	//Sort<int>(a1,9);
	//Sort<double>(a2,9);

	Sort(a1,9);
	Sort(a2,9);

	for(int i=0;i<9;i++)
	{
		cout<<a1[i]<<" ";
	}
	cout<<endl;

	for(int j=0;j<9;j++)
	{
		cout<<a2[j]<<" ";
	}
	cout<<endl;

	return 0;
}

