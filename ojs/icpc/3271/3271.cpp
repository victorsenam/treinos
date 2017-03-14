#include <bits/stdc++.h>

using namespace std;

typedef unsigned int num;

const int N = 22;
const num M = (1u<<20);

pair<int, int> memo[M];
int edge[M];
int par[M];
int from[N];
num obj;
int dest;
int n, m, p;
int hd[N], nx[N*N], to[N*N], es, hw[N*N];
int a, b, l;

pair<int, int> pd (num mask) {
    if ((mask|obj) == mask)
        return make_pair(0, 0);
    
    if (memo[mask].first != -1)
        return memo[mask];

    memo[mask].first = INT_MAX;
    memo[mask].second = INT_MAX;

    for (int i = 0; i < n; i++) {
        if ((mask&(1u<<i)) == 0)
            continue;
        for (int ed = hd[i]; ed != -1; ed = nx[ed]) {
            pair<int, int> loc = pd(mask|(1u<<to[ed]));
            loc.first = max(loc.first, loc.first+hw[ed]);
            loc.second++;
            if (loc < memo[mask]) {
                memo[mask] = loc;
                edge[mask] = ed;
            }
        }
    }

    return memo[mask];
}

int main () {
    int cs = 0;
    while (scanf("%d %d %d", &n, &dest, &m) != EOF && (n != -1)) {
        es = 0;
        for (int i = 0; i < (1u<<n); i++)
            memo[i].first = -1;
        memset(hd, -1, sizeof hd);

        for (int i = 0; i < m; i++){ 
            scanf("%d %d %d", &a, &b, &l);
            a--; b--;
            nx[es] = hd[a]; hd[a] = es; to[es] = b; hw[es] = l; es++;
            nx[es] = hd[b]; hd[b] = es; to[es] = a; hw[es] = l; es++;
        }

        scanf("%d", &p);
        obj = 0u;
        for (int i = 0; i < p; i++) {
            scanf("%d", from+i);
            from[i]--;
            obj |= (1u<<(from[i]));
        }

        printf("Case %d: distance = %d\n", ++cs, pd(1u<<(dest-1)).first);
        int ss = 0;
        int att = (1u<<dest-1);
        par[dest] = -1;
        memset(par, -1, sizeof par);
        while ((att|obj) != att) {
            par[to[edge[att]]] = to[edge[att]^1];
            att |= (1<<to[edge[att]]);
        }
        
        for (int i = 0; i < p; i++) {
            att = from[i];
            printf("   %d", att+1);
            att = par[att];
            while (att != -1) {
                printf("-%d", att+1);
                att = par[att];
            }
            printf("\n");
        }
        printf("\n");
    }
}
