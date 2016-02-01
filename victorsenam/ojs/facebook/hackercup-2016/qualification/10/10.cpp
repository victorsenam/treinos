#include <bits/stdc++.h>

using namespace std;

const int N = 2007;

int n;
int p[N];
int x[N], y[N];

inline int dst (int i, int j)
{ return (x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]); }

bool cmp_dst (int i, int j)
{ return dst(0, i) < dst(0, j); }

int cnt (int n) {
    return n*(n-1)/2;
}

int main () {
    int t, ts;
    scanf("%d", &t);

    ts = 1;
    while (t--) {
        scanf("%d", &n);
        int res = 0;

        for (int i = 0; i < n; i++) {
            scanf("%d %d", x+i, y+i);
            p[i] = i;
        }

        for (int i = 0; i < n; i++) {
            swap(x[0], x[i]);
            swap(y[0], y[i]);
            sort(p+1, p+n, cmp_dst);

            int ls = 1;
            for (int j = 2; j < n; j++) {
                if (dst(0, p[ls]) != dst(0, p[j])) {
                    res += cnt(j-ls);
                    ls = j;
                }
            }
            res += cnt(n-ls);
        }

        printf("Case #%d: %d\n", ts++, res);
    }
}
