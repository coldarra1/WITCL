# include <iostream>
# include <algorithm>
# include <string> 

std::string s;
std::string t;

int main() {
    std::cin >> s >> t;

    std::sort(t.begin(), t.end());

    int j=0;
    for (int i=0; i<s.size(); i++) {
        if (s[i] <= t[j]) {
            std::cout << s[i];
            continue;
        }
         
        else {
            std::cout << t[j++];
        }
    }
     
    return 0;
}

