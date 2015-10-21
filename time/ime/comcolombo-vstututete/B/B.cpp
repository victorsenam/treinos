#include <bits/stdc++.h>

using namespace std;

const int N = 103;
const int M = 20000;

int t, n, m;
int visi[N];
int seen[N];
int a, b;
int hd[N], to[M], nx[M], es;
int pre[N], low[N], ord;
int turn;
int brdcnt, nodecnt, brd;
int deg[N];

int dfs(int u, int fr) {
    if (visi[u] == turn)
        return pre[u];
    
    nodecnt++;

    visi[u] = turn;
    pre[u] = low[u] = ord++;

    for (int ed = hd[u]; ed != -1; ed = nx[ed]) {
        if ((ed|1) == (fr|1))
            continue;
        low[u] = min(low[u], dfs(to[ed], (ed^1)));
    }
    
    if (low[u] == pre[u] && fr != -1) {
        brdcnt++;
        brd = fr;
    }

    return low[u];
}

int dfs2 (int u) {
    if (seen[u] == turn)
        return 0;

    seen[u] = turn;

    if (deg[u] != (nodecnt/2-1))
        return 10000;

    int res = 1;

    for (int ed = hd[u]; ed != -1; ed = nx[ed]) {
        if ((ed|1) == (brd|1))
            continue;
        res += dfs2(to[ed]);
    }
    return res;
}

int main () {
    scanf(" %d", &t);
    int ts = 0;

    while (t--) {
        scanf(" %d %d", &n, &m);
        turn++;

        for (int i = 0; i < n; i++) {
            hd[i] = -1;
            deg[i] = 0;
        }
        
        es = 0;
        for (int i = 0; i < m; i++) {
            scanf(" %d %d", &a, &b);
            a--; b--;
            nx[es] = hd[a]; hd[a] = es; to[es] = b; es++;
            nx[es] = hd[b]; hd[b] = es; to[es] = a; es++;
            deg[a]++;
            deg[b]++;
        }

        ord = 0;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (visi[i] == turn)
                continue;

            brdcnt = nodecnt = 0;
            brd = -1;

            dfs(i, -1);
            
            if (nodecnt%2 || brdcnt == 0)
                continue;

            if (nodecnt == 4) {
                if (brdcnt == 3)
                    ans++;
            } else if (nodecnt == 2) {
                ans++;
            } else if (brdcnt > 1) {
            } else {
                deg[to[brd]]--;
                deg[to[brd^1]]--;

                if (dfs2(to[brd]) != nodecnt/2)
                    continue;
                if (dfs2(to[brd^1]) != nodecnt/2)
                    continue;
                ans++;
            }
        }
        printf("Case #%d: %d\n", ++ts, ans);
    }
}
