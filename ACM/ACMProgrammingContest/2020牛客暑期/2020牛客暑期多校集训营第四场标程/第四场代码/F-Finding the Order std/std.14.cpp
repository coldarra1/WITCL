#include<iostream>
using namespace std;
int main()
{
    int AC,AD,BC,BD;
    int p;
    scanf("%d",&p);
    
    while(p--)
    {
        scanf("%d%d%d%d",&AC,&AD,&BC,&BD);
        if(AD>=BD&&AC>=BC)
        {
            if(AD>AC)printf("AB//CD\n");
            else printf("AB//DC\n");
		}
        else if(AD<=BD&&AC<=BC)
        {	
            if(BD>BC)printf("AB//DC\n");
            else printf("AB//CD\n");
		}
        else
        {
            if(AC<BC)printf("AB//CD\n");
            else printf("AB//DC\n");
        }
	}
    return 0;
}