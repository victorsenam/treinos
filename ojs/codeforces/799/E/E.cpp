
#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 2e6+7;
const ll INF = 2e16;

int n, m, k;

ll c[N], rs;
int ty[N];

int p[4][N], ps[4], sf[4];
ll ac[N];

void endit () {
    if (rs == INF) {
        printf("-1\n");
        exit(0);
    }
    printf("%lld\n", rs);
    exit(0);
}

int main () {
    scanf("%d %d %d", &n, &m, &k);
    rs = INF;

    for (int i = 0; i < n; i++)
        scanf("%lld", &c[i]);

    for (int k = 1; k < 4; k += k) {
        int q, x;
        scanf("%d", &q);
        while (q--) {
            scanf("%d", &x);
            ty[x-1] += k;
        }
    }

    for (int i = 0; i < n; i++)
        p[ty[i]][ps[ty[i]]++] = i;

    for (int k = 0; k < 4; k++) {
        sort(p[k], p[k] + ps[k]);
    }

    ac[0] = 0;
    for (int i = 0; i < ps[3]; i++)
        ac[i+1] = ac[i] + c[p[3][i]];

    for (int k = 0; k < 3; k++) {
        for (int i = 0; i < ps[k]; i++) {
        }
    }

    ll curr = 0;
    for (int both = m; both >= 0; both--) {
        ll cst = INF;
        if (both <= ps[3])
            cst = ac[both];

        for (int x = 1; x < 3; x++) {
            while (sf[x] + both < k) {
                if (sf[x] >= ps[x])
                    endit();

                curr += c[p[x][sf[x]++]];
            }
        }

        while (both + sf[0] + sf[1] + sf[2] < m) {
            int x = 7;
            for (int y = 0; y < 3; y++) {
                if (sf[y] >= ps[y]) continue;

                if (x == 7 || c[p[y][sf[y]]] < c[p[x][sf[x]]])
                    x = y;
            }

            if (x == 7)
                endit();

            curr += c[p[x][sf[x]++]];
        }

        rs = min(rs, cst + curr);
    }
    endit();
}
