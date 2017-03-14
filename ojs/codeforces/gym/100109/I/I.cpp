#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef unsigned long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 2e5+7;

int n;
ll a[N], v[N];
int p[65][N];
int x[65][N];

ll memo[65][N];
int cur;

inline ll pd (int i, int c) {
    if (i == 64) return (c == 0);
    
    ll & me = memo[i][c];
    //if (me != -1) return me;
    if (i > cur) return me;

    me = 0;
    int nz = x[i][n] - x[i][c] + c - x[i][c];
    int nc = c - x[i][c];
    if (!(nz&1))
        me += pd(i+1, nc);

    int nnc = n - x[i][n] + x[i][c];
    int nnz = n - nz;
    if (!(nnz&1))
        me += pd(i+1, nnc);

    return me;
}

int main () {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    scanf("%d", &n);
    //memset(memo, -1, sizeof memo);

    ll mn = ULLONG_MAX;
    for (int i = 0; i < n; i++) {
        scanf("%llu", &a[i]);
        mn = min(mn, a[i]);
    }
    
    ll xx = 0;
    for (int i = 0; i < n; i++)
        xx ^= (a[i] - mn);

    for (int k = 0; k < 64; k++) {
        for (int i = 0; i < n; i++) {
            p[k][i] = i;
            v[i] = (a[i]&((1llu<<k)-1));
        }

        sort(p[k], p[k]+n, [k] (int i, int j) {
            return v[i] < v[j];
        });

        for (int _i = 0; _i < n; _i++) {
            int i = p[k][_i];
            x[k][_i+1] = x[k][_i];
            if (a[i]&(1llu<<k))
                x[k][_i+1]++;
        }
    }

    for (cur = 63; cur >= 0; cur--) {
        for (int i = 0; i <= n; i++)
            pd(cur, i);
    }

    printf("%llu\n", pd(0,0) - !xx);
}
