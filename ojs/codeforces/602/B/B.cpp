#include<bits/stdc++.h>

using namespace std;

const int N = 100007;

int res;
int it, jt;
multiset<int> s;
int n;
int v[N];

int main () {
    scanf("%d", &n);
    
    res = 0;
    it = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", v+i);
        s.insert(v[i]);

        while (*(s.rbegin()) - *(s.begin()) > 1) {
            s.erase(s.find(v[it++]));   
        }

        res = max(res, i-it+1);
    }

    printf("%d\n", res);
}
