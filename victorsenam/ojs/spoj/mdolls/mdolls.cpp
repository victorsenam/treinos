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

int lis[N];
int qtd[N];
int n;
doll v[N];
int rs, ps;
int t;

int main () {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%d %d", &v[i].a, &v[i].b);

        sort(v, v+n);
        
        rs = 0;
        for (int i = 0; i < n; i++) {
            ps = lower_bound(lis, lis+rs, v[i].b) - lis;
            if (ps == rs) {
                qtd[ps] = 0;
                rs++;
            }
            qtd[ps]++;
            lis[ps] = v[i].b;
        }
        int maxi = 0;
        for (int i = 0; i < rs; i++) 
            maxi = max(maxi, qtd[i]);
        printf("%d\n", maxi);
    }
}

