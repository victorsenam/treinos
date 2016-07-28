#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 200011;
const int M = 2*N;

ll memo[M];
int visi[M];
int seen[N];
int hd[N], to[M], nx[M], es;
ll val[M];
int ord[N][2], os;
int v[N];
int pr[N];
int n;
vector<int> its[N];
int bit[N];

void add (int i, ll x) {
    for (i += 3; i < n+3; i+=(i&-i))
        bit[i] += x;
}

ll get (int i) {
    ll x = 0;
    for (i += 3; i > 0; i-=(i&-i))
        x += bit[i];
    return x;
}

ll pd (int fr) {
    ll & me = memo[fr];
    if (visi[fr]) return me;
    visi[fr] = 1;

    me = 0;
    me += val[fr];
    int u = to[fr];
    for (int ed = hd[u]; ed; ed = nx[ed])
        if ((fr|1) != (ed|1))
            me += pd(ed);
    return me;
}

void dfs (int fr) {
    int u = to[fr];
    seen[u] = 1;
    ord[u][0] = os++;
    pr[u] = (fr^1);

    for (int ed = hd[u]; ed; ed = nx[ed]) {
        if ((ed|1) == (fr|1)) continue;
        //assert(to[ed] != pr[u]);
        dfs(ed);
    }

    ord[u][1] = os;
    //DEBUG("%d [%d,%d] from %d(%d)\n", u, ord[u][0], ord[u][1], to[fr], fr);
}

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", v+i);
        its[v[i]].push_back(i);
    }

    es = 2;
    for (int i = 1; i < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        nx[es] = hd[a]; to[es] = b; hd[a] = es++;
        nx[es] = hd[b]; to[es] = a; hd[b] = es++;
    }

    os = 0;
    to[1] = 0;
    dfs(1);

    ll qtd = 0;

    for (int _i = n; _i > 0; _i--) {
        for (int _j = 0; _j < its[_i].size(); _j++) {
            int i = its[_i][_j];

            ll sum = 0;
            //DEBUG("item %d\n", i);
            for (int ed = hd[i]; ed; ed = nx[ed]) {
                if (ed != pr[i]) {
                    val[ed] = get(ord[to[ed]][1]-1) - get(ord[to[ed]][0]-1);
                    sum += val[ed];
                    //DEBUG("%d->%d : %lld\n", to[ed^1], to[ed], val[ed]);
                }
            }
            if (pr[i]) {
                val[pr[i]] = qtd - sum;
                //DEBUG("%d->%d : %lld = %lld - %lld [%d]\n", to[pr[i]^1], to[pr[i]], val[pr[i]], qtd, sum, pr[i]);
            } else {
                //DEBUG("is root\n");
            }
        }
        for (int _j = 0; _j < its[_i].size(); _j++) {
            add(ord[its[_i][_j]][0], 1);
            qtd++;
        }
    }

    for (int i = 2; i < es; i++)
        pd(i);

    int res = 0;
    ll vres = LLONG_MAX;
    for (int i = 0; i < n; i++) {
        ll att = 0;
        for (int ed = hd[i]; ed; ed = nx[ed])
            att += memo[ed];
        //DEBUG("%d : %lld\n", i, att);
        if (att < vres) {
            vres = att;
            res = i;
        }
    }

    printf("%d %lld\n", res+1, vres);
}

