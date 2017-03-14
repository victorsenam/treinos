#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 1e5+7;

vector<int> diag[2][N+N];
int visi[2][2][N+N];
ll res[N];
int n, m, k;
int l, c, d, u;
int p[N][2];

int get(int l, int c, int d) {
    if (d) return l+c;
    else return c-l+N;
}

int main () {
    scanf("%d %d %d", &n, &m, &k);

    for (int i = 0; i < k; i++) {
        scanf("%d %d", &p[i][0], &p[i][1]);
        res[i] = LLONG_MAX;

        diag[0][get(p[i][0],p[i][1],0)].push_back(i);
        diag[1][get(p[i][0],p[i][1],1)].push_back(i);
    }
    //debug("\n");

    l = c = d = u = 0;
    ll rnd = 0;
    bool ok = 0;
    while (true) {
        int rp = get(l,c,d^u);
        //debug("%lld (%d,%d) %d %d : %d\n", rnd, l, c, d, u, rp);
        if (ok) {
            if (l == 0 && c == 0) break;
            if (l == n && c == m) break;
            if (l == n && c == 0) break;
            if (l == 0 && c == m) break;
            if (visi[u][d][rp]) break;
        }
        ok = 1;

        visi[u][d][rp] = 1;

        for (int k : diag[d^u][rp]) {
            res[k] = min(res[k], rnd + abs(l-p[k][0]));
            //debug("%lld hit %d(%d,%d)\n", rnd+abs(l-p[k][0]), k, p[k][0], p[k][1]);
        }

        int ls = 0;
        if (!d) {
            if (!u) {
                ls = min(abs(n-l), abs(m-c));
                l += ls; c += ls;
            } else {
                ls = min(abs(l), abs(m-c));
                l -= ls; c += ls;
            }
        } else {
            if (!u) {
                ls = min(abs(n-l), abs(c));
                l += ls; c -= ls;
            } else {
                ls = min(abs(l), abs(c));
                l -= ls; c -= ls;
            }
        }

        rnd += ls;

        if (l == n)
            u = 1;
        if (c == m)
            d = 1;
        if (l == 0)
            u = 0;
        if (c == 0)
            d = 0;
    }

    for (int i = 0; i < k; i++) {
        if (res[i] == LLONG_MAX)
            printf("-1\n");
        else
            printf("%lld\n", res[i]);
    }
}
