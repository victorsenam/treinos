#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {/*fprintf(stderr, __VA_ARGS__);*/}
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
multiset<pair<int, int> >::iterator it;

bool solve (int mid, int fr) {
    DEBUG("Solving %d(%d) with %d\n", fr, to[fr]+1, mid);
    int u = to[fr];
    int curr = cs[u];
    multiset<pair<int, int> > s;
    
    for (int ed = hd[u]; ed; ed = nx[ed]) {
        if ((ed|1) == (fr|1))
            continue;
        s.insert(make_pair(memo[ed], rm[ed]));
        DEBUG("%d -> (%d,%d)\n", to[ed], memo[ed], rm[ed]);
    }
 
    DEBUG("[[[%d\n", s.size());
    while (!s.empty()) {
        it = s.upper_bound(make_pair(mid-curr, INT_MAX));
        if (it == s.begin())
            return 0;
        --it;
        DEBUG("%d + %d = %d <= ?\n", curr, it->second, curr+it->second);

        curr += it->second;
        s.erase(it);
    }
    return 1;
}

int dp (int fr) {
    if (fr && visi[fr] == turn)
        return memo[fr];
    visi[fr] = turn;

    int & me = memo[fr];
    int u = to[fr];
    me = nd[u];
    int curr = cs[u];
    int maxi = 0;
    
    for (int ed = hd[u]; ed; ed = nx[ed]) {
        if ((ed|1) == (fr|1))
            continue;
        maxi = max(maxi, dp(ed));
        curr += rm[ed];
    }

    int lo = nd[u];
    int hi = curr + maxi;

    while (lo < hi) {
        int mid = (lo+hi)/2;
        if (solve(mid, fr))
            hi = mid;
        else
            lo = mid+1;
    }
    DEBUG("DP %d(%d) -> %d\n", fr, to[fr]+1, lo);
    
    return me = lo;
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
    int ts = 0;
    while (scanf("%d", &n) && n) {
        ++turn;
        es = 2;
        memset(hd, 0, sizeof hd);
        for (int i = 0; i < n; i++) {
            scanf("%d %d %d", nd+i, &aux, cs+i);
            cs[i] += aux;
            nd[i] = max(nd[i], cs[i]);
        }

        for (int i = 1; i < n; i++) {
            scanf("%d %d", to+es, to+es+1);
            to[es]--; to[es+1]--;
            nx[es] = hd[to[es^1]]; hd[to[es^1]] = es; pr[es] = 0; pr[nx[es]] = es; es++;
            nx[es] = hd[to[es^1]]; hd[to[es^1]] = es; pr[es] = 0; pr[nx[es]] = es; es++;
        }

        int mini = INT_MAX;
        for (int i = 2; i < es; i++)
            dfs(i);

        for (int i = 0; i < n; i++) {
            to[0] = i;
            int res = dp(0);
            DEBUG("%d: %d\n", i+1, res);
            mini = min(mini, res);
        }
        printf("Case %d: %d\n", ++ts, mini);
    }
}
        /*
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
        */

