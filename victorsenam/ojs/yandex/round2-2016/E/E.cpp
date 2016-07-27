#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;


const int N = (2e5)+7;
const int M = 3*N;
clock_t t;

struct bit {
    ll v[N];
    
    inline void add (ll i, ll x) {
        for (i += 2; i < N; i+=(i&-i))
            v[i] += x;
    }

    inline ll get (ll i) {
        ll x = 0;
        for (i += 2; i > 0; i-=(i&-i))
            x += v[i];
        return x;
    }
};

int ord[N][2], os;
int li[N], hd[N], to[M], nx[M], es;
int n, cm;
int pr[M];
int v[M];
bit tree;
ll qtd, cst[M];
ll sum;

int visi[N];
ll memo[N];

ll dp (int u) {
    ll & me = memo[u];
    if (visi[u]++) return me;

    if (!u) me = sum;
    else me = dp(to[pr[u]^1]) + cst[pr[u]^1] - cst[pr[u]];

    return me;
}

void dfs (int fr) {
    //assert(os <= n);
    //assert(!fr || (fr >= cm && fr < es));
    int u = to[fr];
    //DEBUG("%d[%d]\n", u+1, fr);
    pr[u] = fr;
    ord[u][0] = os++;
    for (int ed = hd[u]; ed; ed = nx[ed]) {
        if ((ed|1) != (fr|1))
            dfs(ed);
    }
    ord[u][1] = os;
}

int main () {
    t = clock();
    scanf("%d", &n);

    es = 2;
    for (int i = 0; i < n; i++) {
        scanf("%d", v+i);

        nx[es] = li[v[i]]; to[es] = i; li[v[i]] = es++;
    }

    es|=1;
    es++;
    cm = es;
    for (int i = 1; i < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        nx[es] = hd[a]; to[es] = b; hd[a] = es++;
        nx[es] = hd[b]; to[es] = a; hd[b] = es++;
    }

    to[0] = 0;
    os = 0;
    dfs(0);
    qtd = 0;
    sum = 0;


    for (int att = n; att >= 0; att--) {
    //for (int att = 1; att <= n; att++) {
        for (int ps = li[att]; ps; ps = nx[ps]) {
            int u = to[ps];
            int fr = pr[u]; 

            for (int ed = hd[u]; ed; ed = nx[ed]) {
                if ((ed|1) == (fr|1)) continue;
                sum += (cst[ed] = (tree.get(ord[to[ed]][1]-1) - tree.get(ord[to[ed]][0]-1)));
                //DEBUG("%d->%d : %lld\n", to[ed^1]+1, to[ed]+1,  cst[ed]);
            }

            if (fr)
                cst[fr^1] = qtd - (tree.get(ord[u][1]-1) - tree.get(ord[u][0]-1));
            //DEBUG("%d->%d : %lld *\n", to[fr]+1, to[fr^1]+1,  cst[fr^1]);
        }
        for (int ps = li[att]; ps; ps = nx[ps]) {
            qtd++;
            int u = to[ps];
            tree.add(ord[u][0], 1);
        }
    }

    int res = 0;
    ll rval = LLONG_MAX;
    for (int i = 0; i < n; i++) {
        ll loc = dp(i);
        //DEBUG("%d : %lld\n", i+1, loc);
        if (loc < rval) {
            res = i;
            rval = loc;
        }
    }

    printf("%d %lld\n", res+1, rval);
}
