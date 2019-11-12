#include<bits/stdc++.h>		// Enal
 
using namespace std;
 
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;++i){
        char c[200];
        scanf("%s",c);
        int cnt=0,maxnum=0;
        for(int j=0;j<strlen(c);++j){
            if(c[j]=='('){
                ++cnt;
            }else{
                --cnt;
            }
            if(cnt<0){
                puts("-1");
                break;
            }else{
                maxnum=max(cnt,maxnum);
            }
        }
        if(cnt==0){
            cout<<maxnum-1<<endl;
        }else if(cnt>0){
            puts("-1");
        }
    }
    return 0;
}

//# include <iostream>	// kcxz
//# include <cstdio>
//# include <stack>
//# include <string>
//
//std::string s;
//
//void solve() {
//	std::stack <char>stk;
//	int flag = 1;
//	int cnt = 0;
//	int max = 0;
//	std::string::iterator p = s.begin();
//
//	while (p != s.end() && flag) {
//		switch (*p) {
//			case '(': {
//				if (stk.empty()) {
//					cnt = 0;
//				}
//
//				stk.push(*p);
//				++cnt;
//				if (max < cnt) {
//					max = cnt;
//				}
//				
//				break;
//			}
//			case ')': {
//				if (!stk.empty() && stk.top() == '(') {
//					stk.pop();
//					--cnt;
//				} else {
//					flag = 0;
//				}
//				
//				break;
//			}
//			default: {
//				std::cout << "Error\n";
//				break;
//			}
//		}
//		p++;
//	}
//	
//	if (stk.empty() && flag) {
//		std::cout << max - 1 << std::endl;
//	} else {
//		std::cout << "-1" << std::endl;
//	}
//}
//
//int main() {
//	int T;
//	std::cin >> T;
//	while (T--) {
//		std::cin.ignore(1, '\n');
//		std::cin >> s;              // std::cout << s << std::endl;
//		solve();
//	}
//	
//	return 0;
//}

