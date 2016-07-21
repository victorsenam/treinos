#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define GNU __gnu_pbds

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef pair<int, int> pii;
namespace GNU { typedef tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> ordered_set; } 
using GNU::ordered_set;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 200007;
const int M = 2*N;

ll memo[M];
int visi[M];
int hd[N], to[M], nx[M], es;
ll val[M];
int v[N];
ordered_set s[N], gen;
int p[N];
int pr[N];
int n;
int deg[N];
int qu[N], qi, qf;

ll pd (int fr) {
    ll & me = memo[fr];
    if (fr && visi[fr]) return me;
    visi[fr] = 1;

    me = 0;
    me += val[fr];
    int u = to[fr];
    for (int ed = hd[u]; ed; ed = nx[ed])
        if ((fr|1) != (ed|1))
            me += pd(ed);
    return me;
}

void join (int a, int b) {
    if (s[p[a]].size() < s[p[b]].size())
        swap(p[a], p[b]);

    for (pii aux : s[p[b]])
        s[p[a]].insert(aux);
    p[b] = p[a];
}

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", v+i);
        v[i] = n-v[i];
        p[i] = i;
        gen.insert(pii(v[i], i));
        s[i].insert(pii(v[i], i));
    }

    es = 2;
    for (int i = 1; i < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        nx[es] = hd[a]; to[es] = b; hd[a] = es++;
        nx[es] = hd[b]; to[es] = a; hd[b] = es++;
        deg[a]++; deg[b]++;
    }

    for (int i = 0; i < n; i++)
        if (deg[i] == 1)
            qu[qf++] = i;

    while (qi < qf) {
        int u = qu[qi++];
        pr[u] = 0;
        deg[u] = 0;

        for (int ed = hd[u]; ed; ed = nx[ed]) {
            if (deg[to[ed]])
                pr[u] = ed;
        }

        if (pr[u]) {
            int w = to[pr[u]];
            val[pr[u]] = gen.order_of_key(pii(v[u], -1)) - s[p[u]].order_of_key(pii(v[u], -1));
            //DEBUG("%d->%d : %lld = %d - %d\n", u, w, val[pr[u]], (int) gen.order_of_key(pii(v[u], -1)), (int) s[p[u]].order_of_key(pii(v[u], -1)));
            val[pr[u]^1] = s[p[u]].order_of_key(pii(v[w], -1));
            //DEBUG("%d->%d : %lld\n", w, u, val[pr[u]^1]);

            join(u, w);

            deg[w]--;
            if (deg[w] == 1)
                qu[qf++] = w;
        } else {
            assert(qi == qf);
        }
    }

    int res = 0;
    ll vres = LLONG_MAX;
    for (int i = 0; i < n; i++) {
        to[0] = i;
        ll att = pd(0);
        //DEBUG("%d : %lld\n", i, att);
        if (att < vres) {
            vres = att;
            res = i;
        }
    }

    printf("%d %lld\n", res+1, vres);
}
