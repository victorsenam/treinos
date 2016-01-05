#include <bits/stdc++.h>
#define mp make_pair
using namespace std;
typedef long long nu;
typedef int node;
typedef int edge;
const int N = 1e6+1;
const int M = 2*N;

int n;
int hd[N], anc[N], d[N], sz[N], pre[N], val[N];
int to[M], nx[M], w[M], es;
int ps, ts, ls;

namespace lca
{
    int tree[4*N], id[N];
    node cmp(node u, node v)
    { return d[u] < d[v] ? u : v; }
    void build()
    {
        d[n] = INT_MAX;
        for(int i=2*n-2;i>0;--i)
            tree[i] = cmp(tree[i<<1],tree[i<<1|1]);
    }
    node lca(node u, node v)
    {
        node ans = n;
        int l = min(id[u],id[v]),
            r = max(id[u],id[v])+1;
        for(;l<r;l>>=1,r>>=1)
        {
            if(l&1) ans = cmp(ans, tree[l++]);
            if(r&1) ans = cmp(ans, tree[--r]);
        }
        return ans;
    }
}

namespace hld
{
    int tree[2*N], chain[N], id[N], leaf[N];
    node cmp(node u, node v)
    { return val[u] < val[v]? u : v; }
    void build()
    {
        for(int i=0;i<n;i++)
            chain[pre[i]] = chain[chain[pre[i]]];
        int ts = n;
        while(ls > 0)
        {
            node u = leaf[--ls];
            while(u != chain[u])
            {
                tree[id[u]=ts++] = u;
                u = anc[u];
            }
            tree[id[u]=ts++] = u;
        }
        val[n] = INT_MAX;
        for(int i=n-1;i>0;--i)
            tree[i] = cmp(tree[i<<1],tree[i<<1|1]);
    }
    void update(int p)
    {
        if(!p) return;
        if(p<n) tree[p] = cmp(tree[p<<1],tree[p<<1|1]);
        update(p>>1);
    }
    node query(int l, int r)
    {
        node ans = n;
        if(l >= r) return ans;
        if(l&1) ans = cmp(ans, tree[l++]);
        if(r&1) ans = cmp(ans, tree[--r]);
        return cmp(ans, query(l>>1,r>>1));
    }
    node climb(node u, node v)
    {
        node ans = n;
        while(chain[u] != chain[v])
        {
            ans = cmp(ans, query(id[u],id[chain[u]]+1));
            u = anc[chain[u]];
        }
        return cmp(ans, query(id[u], id[v]+1));
    }
    node ans(node u, node v)
    {
        node a = lca::lca(u,v);
        return cmp(climb(u,a),climb(v,a));
    }
}

int dfs(node u, int d)
{
    int spc = u, bst = 0;
    ::d[u] = d;
    hld::chain[u] = u;
    lca::tree[lca::id[u]=ts++] = u;
    pre[ps++] = u;
    sz[u] = 1;
    for(edge e=hd[u];e!=-1;e=nx[e])
        if(sz[to[e]] == -1)
        {
            anc[to[e]] = u;
            dfs(to[e], d+1);
            lca::tree[ts++] = u;
            sz[u] += sz[to[e]];
            if(sz[to[e]] > bst)
                bst = sz[to[e]], spc = to[e];
        }
    hld::chain[spc] = u;
    if(sz[u] == 1)
        hld::leaf[ls++] = u;
}

int q;
int main()
{
    memset(hd, -1, sizeof hd); es = 0;
    memset(sz, -1, sizeof sz);
    scanf(" %d%d", &n, &q);
    for(int i=0;i<n-1;i++)
    {
        node u, v;
        scanf(" %d%d", &u, &v); --u; --v;
        to[es] = v; nx[es] = hd[u]; hd[u] = es++;
        to[es] = u; nx[es] = hd[v]; hd[v] = es++;
    }
    for(node u=0;u<n;u++)
        val[u] = INT_MAX;
    anc[0] = 0;
    ps = 0; ts = 2*n-1; dfs(0,0);
    lca::build();
    hld::build();
    while(q--)
    {
        int cmd; node u;
        scanf(" %d%d", &cmd, &u); u--;
        if(cmd == 1)
        {
            node v = hld::climb(u,0);
            if(v == n) v = -1;
            else v++;
            printf("%d\n", v);
        }
        else
        {
            if(val[u] == d[u])
                val[u] = INT_MAX;
            else val[u] = d[u];
            hld::update(hld::id[u]);
        }
    }
}
