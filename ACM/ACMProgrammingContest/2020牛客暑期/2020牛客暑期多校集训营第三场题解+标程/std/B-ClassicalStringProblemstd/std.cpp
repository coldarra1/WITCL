#include<cstdio>
#include<cstring>
const int SIZE = 500001;
char s[SIZE];
int main(){
	scanf("%s",s);
	int n=strlen(s);
	int Q;
	scanf("%d",&Q);
	int offset=0;
	while(Q--){
		char c[4];
		scanf("%s",c);
		if(c[0]=='M'){
			int x;
			scanf("%d",&x);
			offset=(offset+x+n)%n;
		}
		else{
			int x;
			scanf("%d",&x);
			printf("%c\n",s[(offset+x-1)%n]);
		}
	}
	return 0;
}
