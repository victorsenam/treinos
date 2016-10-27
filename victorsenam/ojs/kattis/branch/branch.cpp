#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 5e3+7;
const int M = 1e5+7;

int n, m, k, q;
int hd[N], to[M], nx[M], es;
ll wg[M];
ll dist[2][N];
int seen[2][N];
int visi[2][N];
ll memo[2][N];
ll acc[N];
ll v[N];
int w;

struct node {
    int u;
    ll d;
    int t;

    bool operator < (const node & ot) const {
        if (d != ot.d) return d > ot.d;
        if (t != ot.t) return t > ot.t;
        return u > ot.u;
    }
};

void djs (int r) {
    node att;
    att.u = r;
    att.d = 0;
    dist[0][att.u] = dist[1][att.u] = 0;
    visi[0][att.u] = visi[1][att.u] = 1;

    priority_queue<node> pq;
    att.t = 0;
    pq.push(att);
    att.t = 1;
    pq.push(att);

    while (!pq.empty()) {
        att = pq.top();
        pq.pop();

        if (seen[att.t][att.u]) continue;
        seen[att.t][att.u] = 1;


        for (int ed = hd[att.u]; ed; ed = nx[ed]) {
            if ((ed^att.t)&1) continue;
            node nex = att;
            nex.u = to[ed];
            nex.d += wg[ed];
            
            if (!visi[nex.t][nex.u]) {
                visi[nex.t][nex.u] = 1;
                dist[nex.t][nex.u] = nex.d + 1;
            }
            
            if (dist[nex.t][nex.u] <= nex.d) continue;

            dist[nex.t][nex.u] = nex.d;
            pq.push(nex);
        }
    }
}

void solve (int a, int b, int l, int r) {
    if (a > b) return;
    int c = (a+b)/2;

    int x = min(l, c-1);
    memo[w&1][c] = (acc[c] - acc[x])*ll(c-x-1) + memo[!(w&1)][x];
    for (int i = x; i <= r && i < c; i++) {
        ll loc = (acc[c] - acc[i])*ll(c-i-1) + memo[!(w&1)][i];
        if (i == x || loc < memo[w&1][c]) {
            x = i;
            memo[w&1][c] = loc;
        }
    }

    solve(a, c-1, l, x);
    solve(c+1, b, x, r);
}

int main () {
    scanf("%d %d %d %d", &n, &q, &k, &m);
    es = 2;

    for (int i = 0; i < m; i++) {
        int a, b;
        ll l;
        scanf("%d %d %lld", &a, &b, &l);
        a--; b--;

        wg[es] = l; to[es] = b; nx[es] = hd[a]; hd[a] = es++;
        wg[es] = l; to[es] = a; nx[es] = hd[b]; hd[b] = es++;
    }

    djs(q);
    for (int i = 0; i < q; i++) {
        v[i] = dist[0][i] + dist[1][i];
    }

    swap(v[0], v[q]);
    sort(v+1, v+q+1);

    acc[0] = 0;
    for (int i = 1; i <= q; i++) {
        acc[i] = acc[i-1] + v[i];
    }

    memo[0][0] = 0;
    for (int i = 1; i <= q; i++)
        memo[0][i] = acc[i]*ll(i-1);

    for (w = 1; w < k; w++) {
        solve(1, q, 0, q);
    }
    printf("%lld\n", memo[!(k&1)][q]);
}
