#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 107;
const int M = 2*N;

int n;
int hd[N], to[M], nx[M], pr[M], es;
int cs[N], nd[N], aux;
int rm[M];
int vs[M], turn;
int memo[M], visi[M];

int dp (int fr) {
    if (fr && visi[fr] == turn)
        return memo[fr];
    visi[fr] = turn;

    int & me = memo[fr];
    int u = to[fr];
    me = 0;


}

int dfs (int fr) {
    if (vs[fr] == turn)
        return rm[fr];
    vs[fr] = turn;

    int u = to[fr];
    rm[fr] = cs[u];
    for (int ed = hd[u]; ed; ed = nx[ed]) {
        if ((fr|1) == (ed|1)) continue;
        rm[fr] += dfs(ed);
    }

    return rm[fr];
}

int main () {
    while (scanf("%d", &n) && n) {
        ++turn;
        es = 2;
        memset(hd, 0, sizeof hd);
        for (int i = 0; i < n; i++) {
            scanf("%d %d %d", nd+i, &aux, cs+i);
            cs[i] += aux;
        }

        for (int i = 1; i < n; i++) {
            scanf("%d %d", to+es, to+es+1);
            to[es]--; to[es+1]--;
            nx[es] = hd[to[es^1]]; hd[to[es^1]] = es; pr[es] = 0; pr[nx[es]] = es; es++;
            nx[es] = hd[to[es^1]]; hd[to[es^1]] = es; pr[es] = 0; pr[nx[es]] = es; es++;
        }

        for (int i = 2; i < es; i++)
            dfs(i);

        for (int i = 0; i < n; i++) {
            nx[0] = hd[i];
            pr[hd[i]] = 0;

            DEBUG("%d:", i+1);
            for (int ed = hd[i]; ed; ed = nx[ed])
                DEBUG(" %d(%d)", to[ed]+1, rm[ed]);
            DEBUG("\n");

            hd[i] = 0;
            while (nx[0]) {
                int maxi = nx[0];
                for (int ed = nx[0]; ed; ed = nx[ed])
                    if (rm[ed] > rm[maxi])
                        maxi = ed;

                nx[pr[maxi]] = nx[maxi];
                pr[nx[pr[maxi]]] = pr[maxi];
                
                nx[maxi] = hd[i];
                pr[hd[i]] = maxi;
                pr[maxi] = 0;
                hd[i] = maxi;
            }
            
            DEBUG("%d:", i+1);
            for (int ed = hd[i]; ed; ed = nx[ed])
                DEBUG(" %d(%d)", to[ed]+1, rm[ed]);
            DEBUG("\n");
        }

        int mini = INT_MAX;
        for (int i = 0; i < n; i++) {
            to[0] = i;
            mini = min(mini, dp(0));
        }
    }
}
