#include<bits/stdc++.h>
using namespace std;

string s1[4]={"AFS","FNC","KT","RNG"};
string s2[4]={"C9","EDG","G2","IG"};
string s[1000];
map<string,int> a;

int main()
{
	a["AFS"]=1; a["G2"]=1;
	a["RNG"]=2; a["C9"]=2;
	a["KT"]=3; a["EDG"]=3;
	a["FNC"]=4; a["IG"]=4;
	int i,i1,i2,i3,i4,j1,j2,j3,j4,x=0;
	string t1,t2,t3,t4,t5,t6,t7,t8,tt;
	for (i1=0;i1<4;i1++)
	{
		t1=s1[i1];
		for (j1=0;j1<4;j1++)
		{
			t2=s2[j1];
			for (i2=0;i2<4;i2++)
				if (i2!=i1)
				{
					t3=s1[i2];
					for (j2=0;j2<4;j2++)
						if (j2!=j1)
						{
							t4=s2[j2];
						for (i3=0;i3<4;i3++)
							if (i3!=i1 && i3!=i2)
							{
								t5=s1[i3];
								for (j3=0;j3<4;j3++)
								if(j3!=j1 && j3!=j2)
								{
									t6=s2[j3];
									for (i4=0;i4<4;i4++)
										if ((i4!=i3) && (i4!=i2) && (i4!=i1))
										{
											t7=s1[i4];
											for (j4=0;j4<4;j4++)
												if (j4!=j3 && j4!=j2 && j4!=j1)
												{
													t8=s2[j4];
													if ((a[t1]!=a[t2] && a[t1]!=a[t3] && a[t1]!=a[t4] && a[t2]!=a[t3] && a[t2]!=a[t4] && a[t3]!=a[t4]) && (a[t5]!=a[t6] && a[t5]!=a[t7] && a[t5]!=a[t8] && a[t6]!=a[t7] && a[t6]!=a[t8] && a[t7]!=a[t8]) )
													{
														tt=t1+" "+t2+" "+t3+" "+t4+" "+t5+" "+t6+" "+t7+" "+t8;
														x++;
														s[x]=tt;
													}
												}
										}
								}
							}
						}
				}
		}
	}
	cout<<x<<endl;
	for (i=1;i<=x;i++)
		cout<<s[i]<<endl;
	return 0;
}
