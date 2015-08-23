#include <bits/stdc++.h>

using namespace std;

set<int> s;
set<int>::iterator it;
int a;

int main () {
    s.insert(0);
    s.insert(INT_MAX);
    
    while (scanf("%d", &a) != EOF) {
        it = s.insert(a).first;
        
        it--;
        printf("%d ", *it);
        it++;
        printf("%d ", *it);
        it++;
        printf("%d\n", *it);

        for (it = s.begin(); it != s.end(); it++) printf("%d ", *it);
        printf("\n");
    }
}
