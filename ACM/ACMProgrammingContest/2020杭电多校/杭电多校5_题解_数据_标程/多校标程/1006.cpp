#include<bits/stdc++.h>
using namespace std;
#define mem(X) memset(X,0,sizeof(X))
#define mes(X,Y) memset(X,Y,sizeof(X))
#define dd(X) if (DBG) cout<<#X<<"="<<X<<' ';
#define de(X) if (DBG) cout<<#X<<"="<<X<<'\n';
#define fi first
#define se second
#define vi vector<int>
#define pb push_back
#define sz(X) ( (int)(X.size()) )
#define pii pair<ll,ll>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)//����ұ�
using namespace std;
typedef long long ll;
const int SI=1e5+100;
const int DBG=1;
const int MAXN=1e5+100;
int n,k,v,q;
int bit[SI];
void update(int pos,int val)
{
	while( pos<=n ){
		bit[pos]=max(bit[pos],val);
		pos+=pos&(-pos);
	}
}
int query(int pos)
{
	int res=0;
	while(pos>0){
		res=max(res,bit[pos]);
		pos-=pos&(-pos);
	}
	return res;
}
int a[SI];
bool del[SI]; 
int num[SI];//num[i]ȡ��������Ϳ��Դճɳ���Ϊi�������е��������� // num[1]=n 
void didall()
{
	for( int i=1;i<=q;i++ )
		{
			update(a[i],query(a[i]-1)+1);
			del[ a[i] ]=true;
		}
	for( int i=1;i<=n;i++ )
		{
			if ( del[i] )
				continue;
			num[ query(i-1)+1 ]++; 
		}
}
void didv1()
{
	if ( num[k]>0 )//ֱ��ȡ���ճɴ� 
		{
			printf("YES %d\n",num[k]);		
			return ;
		}
	int last=n-q,sum=0;
	if ( last&1 )
		{
			for( int i=1;i<k-1;i++ )
				sum+=num[i];
			if ( num[k-1]>0 )
				sum++;
			printf("YES %d\n",sum);			
		}
	else
		printf("NO\n");
}
void didv2()
{
	if ( num[k-1]>=2 )//����2ֻ��һ�� 
		{
			printf("YES 1\n");
			return;
		}
	int sa=0;
	for( int i=1;i<=k-1;i++ )
		sa+=num[i];
	if ( sa&1 )
		{
			int sum=0;
			for( int i=1;i<k-2;i++ )
				sum+=num[i];
			if ( num[k-1]==1 )
				{
					if ( num[k-2]>0 )
						sum+=2;//ɾ�����һ�� ����  �����ڶ������һ��
					else
						sum+=1;//ֻ��ɾ�����һ�� 
				}
			else
				{
					if ( num[k-2]>=2 )
						sum+=2;//ɾ�������ڶ��е����һ�����ߵ����ڶ��� 
					else
						sum+=num[k-2];
				}
			printf("YES %d\n",sum);
		}
	else
		printf("NO\n");
}
int main()
{
	int TTT;
	scanf("%d",&TTT);
	while(TTT--)
		{
			scanf("%d %d %d %d",&n,&v,&q,&k);
			for( int i=1;i<=q;i++ )
				scanf("%d",&a[i]);
			for( int i=1;i<=max(n,k);i++ )//��ʼ����״���� 
				{
					bit[i]=0;
					num[i]=0;
					del[i]=false;
				}
			didall();
			if ( v==1 )
				didv1();
			else
				didv2();
		}
    return 0;
}
