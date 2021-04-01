#include<bits/stdc++.h>
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1,w=n;i<=n;i++,w--)
		for(int x=i,j=0;x>=1&&j<w;x-=2,j++)
			for(int y=x,k=0;y>=1&&k<w;y--,k++)
				printf("%d %d %d\n",i+k+j,k-j,y);
	return 0;
}