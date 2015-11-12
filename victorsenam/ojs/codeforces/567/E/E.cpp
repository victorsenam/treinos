// WA
#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef ll num;
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif

const int N = 200007;

struct vert {
    int u;
    num d;

    inline bool operator < (const vert & ot) const
    { return d > ot.d; }
};

int n, m;
int src, snk;
int hd[N], nx[N], to[N], es;
num wg[N];
bool visi[2][N];
int st[N], pre[N], low[N], cnt;
int ans[N];
num dist[2][N];
num sp;

inline void connect (int a, int b, int w) 
{ nx[es] = hd[a]; hd[a] = es; to[es] = b; wg[es] = w; es++; }

void djs (int src, bool ty) {
    priority_queue<vert> pq;
    vert att;
    att.u = src;
    att.d = 0;
    pq.push(att);

    while (!pq.empty()) {
        att = pq.top();
        pq.pop();


        if (visi[ty][att.u])
            continue;
        visi[ty][att.u] = 1;
        dist[ty][att.u] = att.d;

        for (int ed = hd[att.u]; ed != -1; ed = nx[ed]) {
            if ((ed&1) != ty)
                continue;

            vert nex = att;
            nex.u = to[ed];
            nex.d += wg[ed];

            if (visi[ty][nex.u])
                continue;
            
            pq.push(nex);
        }
    }
}

int dfs (int u, int fr) {
    if (st[u] == 2)
        return INT_MAX;
    if (st[u] == 1)
        return pre[u];

    st[u] = 1;
    pre[u] = low[u] = cnt++;
    
    for (int ed = hd[u]; ed != -1; ed = nx[ed]) {
        if ((ed|1) == (fr|1))
            continue;
        if (dist[!(ed&1)][to[ed]] + wg[ed] != dist[!(ed&1)][u])
            continue;

        int val = dfs(to[ed], ed);

        low[u] = min(low[u], val);
    }

    st[u] = 2;
    
    if ( low[u] == pre[u] && fr >= 0 )
        ans[fr] = 1;

    return low[u];
}

void solve (int ed) {
    if (ans[ed] == 1) {
        bool un = 1;
        for (int at = hd[to[ed^1]]; at != -1 && un; at = nx[at]) {
            if (at == ed)
                continue;
            if (to[at] == to[ed] && wg[ed] == wg[at])
                un = 0;
        }
        if (un) {
            printf("YES\n");
            return;
        }
    } 


    num di = INT_MAX;

    if (visi[0][to[ed^1]] && visi[1][to[ed]])
        di = min(di, dist[0][to[ed^1]] + dist[1][to[ed]]);

    num x = sp - 1 - di;

    if (x < 1 || x >= wg[ed] || di == INT_MAX)
        printf("NO\n");
    else
        printf("CAN %I64d\n", wg[ed] - x);
}

int main () {
    scanf("%d %d %d %d", &n, &m, &src, &snk);
    src--; snk--;

    memset(hd, -1, sizeof hd);

    es = 0;
    for (int i = 0; i < m; i++){ 
        int a, b;
        num w;
        scanf("%d %d %I64d", &a, &b, &w);
        a--; b--;

        connect(a, b, w);
        connect(b, a, w);
    }

    djs(src, 0);
    djs(snk, 1);

    dfs(src, -1);

    sp = dist[0][snk];

    for (int i = 0; i < es; i += 2) solve(i);
}

