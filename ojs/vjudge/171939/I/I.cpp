#include <bits/stdc++.h>
using namespace std;
#define pb push_back

typedef long long ll;
typedef pair<ll,ll> pii;

int nx[3009][3009];
inline int nx_eq(int i, int x) {
    return nx[x][i];
}

int a[3][3123];
int dp[2][3009][3009];
int n;
int jb[2][3009];

int best[3009];

inline int lim(int r) {
    return r * 225 + 100;
}

inline int solve(int i, int j, int sz, bool calc=false) {
    if(sz == 0) return 0;
    if(i < 0 || j < 0) return INT_MAX;
    int &r = dp[sz & 1][i][j];
    if(j < jb[sz&1][i]) return r = INT_MAX;
    if(i >= lim(sz) || j >= lim(sz)) return best[sz];
    if(!calc) return r;
    r = min(solve(i - 1, j, sz), solve(i, j - 1, sz));
    if(a[0][i] == a[1][j]) {
        int p = solve(i - 1, j - 1, sz - 1);
        if(p < n)
            r = min(r, nx_eq(p, a[0][i]) + 1);
    }
    return r;
}

int f[3123];

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t, i, j, k;
    t = 5;
#ifndef deb
    cin >> t;
#endif
    while(t--) {
        n = 3000;
#ifndef deb
        cin >> n;
#endif
        for(i = 1; i <= n; i++) f[i] = 0;
        for(k = 0; k < 3; k++)
            for(i = 0; i < n; i++) {
                a[k][i] = (rand() % n) + 1;
#ifndef deb
                cin >> a[k][i];
#endif
                f[a[k][i]]++;
            }
        int val = 0;
        for(i = 1; i <= n; i++)
            val += f[i] * f[i] * f[i];
        printf("val %d\n", val);
        continue;
        for(i = 1; i <= n; i++)
            nx[i][n] = n;
        for(i = n - 1; i >= 0; i--) {
            for(j = 1; j <= n; j++)
                nx[j][i] = nx[j][i + 1];
            nx[a[2][i]][i] = i;
        }
        for(i = 0; i < n; i++)
            jb[0][i] = jb[1][i] = 0;
        for(k = 1; ; k++) {
#ifdef deb
            printf("k %d\n", k);
#endif
            for(i = 0; i < n && i < lim(k); i++)
                for(j = jb[k & 1][i]; j < n && j < lim(k); j++) {
                    if(solve(i, j, k, true) > n) {
                        jb[k & 1][i] = j + 1;
                    }
                }
            best[k] = solve(min(n, lim(k)) - 1, min(n, lim(k)) - 1, k);
            for(i = 0; i < n; i++)
                jb[!(k&1)][i] = jb[k&1][i];
            if(solve(n - 1, n - 1, k) > n) {
                cout << k - 1 << '\n';
                break;
            }
        }
    }
}
