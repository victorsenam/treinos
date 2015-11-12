// INCOMPLETO
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
    int d;

    inline bool operator < (const vert & ot) const
    { return d < ot.d; }
};

int n, m;
int src, snk;
int hd[N], nx[N], to[N], wg[N], es;
bool visi[2][N];
int st[N], pre[N], low[N], cnt;
int ans[N];
int dist[2][N];
int sp;

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
        if (ed&1)
            continue;
        if (dist[0][u] + wg[ed] != dist[0][to[ed]])
            continue;
            
        low[u] = min(low[u], dfs(to[ed], ed));
    }

    st[u] = 2;
    
    if ( low[u] == pre[u] && fr >= 0)
        ans[fr] = 1;

    return low[u];
}

void solve (int ed) {
    if (ans[ed] == 1) {
        printf("YES\n");
    } else {
        int di = INT_MAX;
        if (visi[0][to[ed]] && visi[1][to[ed^1]])
            di = min(di, dist[0][to[ed]] + dist[1][to[ed^1]]);

        if (visi[0][to[ed^1]] && visi[1][to[ed]])
            di = min(di, dist[0][to[ed^1]] + dist[1][to[ed^1]]);

        int x = sp - 1 - x;

        if (x < 1)
            printf("NO\n");
        else
            printf("CAN %d\n", wg[ed] - x);
    }
}

int main () {
    scanf("%d %d %d %d", &n, &m, &src, &snk);
    src--; snk--;

    memset(hd, -1, sizeof hd);

    es = 0;
    for (int i = 0; i < m; i++){ 
        int a, b, w;
        scanf("%d %d %d", &a, &b, &w);
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

