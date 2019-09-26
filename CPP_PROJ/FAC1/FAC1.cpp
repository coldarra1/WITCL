#include <iostream>

using namespace std;

int main()
{
	int n,fac,i;

	cin>>n;

	fac=1;

	for(i=1;i<=n;i++)
	{
		fac*=i;
	}

	cout<<"Fac="<<fac<<endl;

	return 0;
}

