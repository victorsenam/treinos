// Dinicão da massa
#include <bits/stdc++.h>
using namespace std;
typedef int num;

const int N = 3000;
const int M = 2*N;

struct dinic {
    int hd[N], nx[M], to[M], ht[M], es;
    num fl[M], cp[M];
    int n, src, snk;
    int dist[N], seen[N], visi[N], turn;
    int qi, qf, qu[N];

    inline void init () // antes de montar o grafo
    { es = 2; }

    inline void reset () {
        es = 2;
        memset(hd, 0, sizeof hd);
        memset(fl, 0, sizeof fl);
        memset(seen, 0, sizeof seen);
        memset(visi, 0, sizeof visi);
    }

    inline void connect (int i, int j, num cap) {
 //       printf("%d-%d [%lld]\n", i, j, cap);
        nx[es] = hd[i]; hd[i] = es; to[es] = j; cp[es] = cap; fl[es] = 0; es++; 
        nx[es] = hd[j]; hd[j] = es; to[es] = i; cp[es] = fl[es] = 0; es++;
    }

    int notcovered () {
        int res = 0;
        for (int ed = hd[src]; ed; ed = nx[ed])
            if (fl[ed] != cp[ed])
                res++;
        for (int ed = hd[snk]; ed; ed = nx[ed])
            if (fl[ed^1] != cp[ed^1])
                res++;
        return res;
    }

    bool bfs () {
        turn++;
        qi = qf = 0;

        qu[qf++] = snk;
        dist[snk] = 0;
        seen[snk] = turn;

        while (qi < qf) {
            int u = qu[qi++];

            if (visi[u] == turn)
                continue;
            visi[u] = turn;

            for (int ed = hd[u]; ed; ed = nx[ed]) {
                if (cp[ed^1] == fl[ed^1])
                    continue;
                int v = to[ed];

                if (seen[v] == turn && dist[v] <= dist[u]+1)
                    continue;
                seen[v] = turn;
                dist[v] = dist[u]+1;
                qu[qf++] = v;
            }
        }

        return (seen[src] == turn);
    }

    num dfs (int u, num flw) {
        if (u == snk || flw == 0)
            return flw;

        for (int & ed = ht[u]; ed; ed = nx[ed]) {
            int v = to[ed];
            if (fl[ed] >= cp[ed] || seen[v] != turn || dist[v]+1 != dist[u])
                continue;
            if (num ret = dfs(v, min(flw, cp[ed] - fl[ed]))) {
                fl[ed] += ret;
                fl[ed^1] -= ret;
                return ret;
            }
        }

        return 0;
    }

    num debug () {
        for (int i = 0; i < n; i++){ 
            printf("%d:", i);
            for (int ed = hd[i]; ed; ed = nx[ed])
                printf(" %d[%lld/%lld]", to[ed], fl[ed], cp[ed]);
            printf("\n");
        }
    }

    num maxflow () {
        num res = 0;
        while (bfs()) {
            for (int i = 0; i < n; i++)
                ht[i] = hd[i];
            while (num val = dfs(src, (((num(1)<<(numeric_limits<num>::digits-1))-1)<<1) ))
                res += val;
        }
        return res;
    }
};

map<string, int> mp[2];
char inp[N][2][30];
int ts;
dinic flow;
int n;

int main () {
    scanf("%d", &ts);

    for (int tt = 1; tt <= ts; tt++) {
        scanf("%d", &n);
        mp[0].clear(); mp[1].clear();
        
        for (int i = 0; i < n; i++) {
            scanf(" %s %s", inp[i][0], inp[i][1]);

            for (int k = 0; k < 2; k++) {
                if (mp[k].find(inp[i][k]) != mp[k].end()) continue;
                int sz = mp[k].size();
                mp[k][inp[i][k]] = sz;
            }
        }
        int sz = max(mp[0].size(), mp[1].size());

        flow.reset();
        flow.src = 2*sz;
        flow.snk = flow.src+1;
        flow.n = flow.snk+1;
        for (int i = 0; i < mp[0].size(); i++)
            flow.connect(flow.src, i, 1);

        for (int i = sz; i < sz+mp[1].size(); i++)
            flow.connect(i, flow.snk, 1);
            /*

        for (int i = 0; i < mp[0].size(); i++)
            for (int j = sz+mp[1].size(); j < sz+sz; j++)
                flow.connect(i, j, 1);

        for (int i = mp[0].size(); i < sz; i++)
            for (int j = sz; j < sz+mp[1].size(); j++)
                flow.connect(i, j, 1);
                */

        for (int i = 0; i < n; i++) {
            int a = mp[0][inp[i][0]];
            int b = mp[1][inp[i][1]] + sz;
            flow.connect(a, b, 1);
        }

        int res = n- flow.maxflow();
        res -= flow.notcovered();

        printf("Case #%d: %d\n", tt, res);
    }
}
