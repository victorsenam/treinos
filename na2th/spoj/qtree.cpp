#include <bits/stdc++.h>
#define mp make_pair
using namespace std;
typedef long long num;
typedef int node;
typedef int edge;
const int N = 1e4+1;
const int M = 2*N;

int n;
int hd[N], d[N], sz[N], anc[N], pre[N], val[N];
int to[M], nx[M], w[M], es;
int ps, ls;

namespace hld
{
    int tree[2*N], id[N], chain[N], leaf[N];
    node cmp(node u, node v)
    { return val[u] < val[v]? v : u; }
    void build()
    {
        val[n] = INT_MIN;
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
        for(int i=n-1;i>0;--i)
            tree[i] = cmp(tree[i<<1], tree[i<<1|1]);
    }
    void update(int p)
    {
        if(!p) return;
        if(p < n) tree[p] = cmp(tree[p<<1],tree[p<<1|1]);
        update(p>>1);
    }
    node t_query(int l, int r)
    {
        node ans = n;
        if(l >= r) return ans;
        if(l&1) ans = cmp(ans, tree[l++]);
        if(r&1) ans = cmp(ans, tree[--r]);
        return cmp(ans, t_query(l>>1,r>>1));
    }
    node query(node u, node v)
    {
        node ans = n;
        while(chain[u] != chain[v])
        {
            if(d[chain[u]] < d[chain[v]]) swap(u,v);
            ans = cmp(ans, t_query(id[u],id[chain[u]]+1));
            u = anc[chain[u]];
        }
        if(id[u] > id[v]) swap(u,v);
        return cmp(ans, t_query(id[u], id[v]));
    }
}

void dfs(node u, int d)
{
    int spc = u, bst = 0;
    ::d[u] = d;
    hld::chain[u] = u;
    pre[ps++] = u;
    sz[u] = 1;
    for(edge e=hd[u];e!=-1;e=nx[e])
        if(sz[to[e]] == -1)
        {
            anc[to[e]] = u;
            dfs(to[e], d+1);
            sz[u] += sz[to[e]];
            if(sz[to[e]] > bst)
                bst = sz[to[e]], spc = to[e];
        }
    hld::chain[spc] = u;
    if(sz[u] == 1) hld::leaf[ls++] = u;
}

void prepare(node u, int v)
{
    val[u] = v;
    for(edge e=hd[u];e!=-1;e=nx[e])
        if(val[to[e]] == -1)
            prepare(to[e], w[e]);
}

int t;
int main()
{
    scanf(" %d", &t);
    while(t--)
    {
        memset(hd, -1, sizeof hd);
        memset(sz, -1, sizeof sz);
        memset(val, -1, sizeof val);
        es = 0;
        scanf(" %d", &n);
        for(int i=0;i<n-1;i++)
        {
            node u, v; int c;
            scanf(" %d%d%d", &u, &v, &c); --u; --v;
            to[es] = v; w[es] = c;
            nx[es] = hd[u]; hd[u] = es++;

            to[es] = u; w[es] = c;
            nx[es] = hd[v]; hd[v] = es++;
        }
        prepare(0, INT_MIN);
        ls = ps = 0;
        anc[0] = 0; val[0] = INT_MIN;
        dfs(0,0);
        hld::build();
        char cmd = 0;
        while(cmd != 'D')
        {
            scanf(" %c%*s", &cmd);
            if(cmd == 'D') continue;
            int x, y;
            scanf(" %d%d", &x, &y); x--;
            if(cmd == 'Q')
                printf("%d\n", val[hld::query(x, --y)]);
            else
            {
                node u = to[x<<1],
                     v = to[x<<1|1],
                     t = d[u] < d[v] ? v : u;
                val[t] = y;
                hld::update(hld::id[t]);
            }
        }
    }
}
