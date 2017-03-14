#include <bits/stdc++.h>

using namespace std;

const int N = 20007;

struct doll {
    int a;
    int b;
    bool operator < (doll d) {
        if (a != d.a) return a < d.a;
        return b > d.b;
    }
};

int n;
doll v[N];
int rs, ps;
int t;
multiset<int> s;
multiset<int>::iterator it;

int main () {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%d %d", &v[i].a, &v[i].b);

        sort(v, v+n);
        
        rs = 0;
        s.clear();
        for (int i = 0; i < n; i++) {
            it = s.lower_bound(v[i].b);
            if (s.empty() || it == s.begin() || *s.begin() >= v[i].b) {
                s.insert(v[i].b);
                rs++;
            } else {
                it--;
                s.erase(it);
                s.insert(v[i].b);
            }   
        }
        printf("%d\n", rs);
    }
}

