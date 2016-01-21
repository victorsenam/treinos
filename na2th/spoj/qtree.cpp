#include <bits/stdc++.h>
#define mp make_pair
using namespace std;
typedef long long num;
typedef int node;
typedef int edge;
const int N = 1e4+1;
const int M = 2*N+2;

int n;
int hd[N], val[N];
int to[M], nx[M], w[M], es;

int chain[N], anc[N], id[N], leaf[N], d[N], sz[N], tree[2*N];
int ps, ls;
int dfs(node u, node p)
{
    int bst = 0, spc = u;
    sz[id[ps++] = u] = 1;
    d[u] = d[anc[u]=p]+1;
    for(edge e=hd[u];e;e=nx[e])
        if(sz[to[e]] == 0)
        {
            sz[u] += dfs(to[e], u);
            if(sz[to[e]] > bst)
                bst = sz[to[e]], spc = to[e];
        }
    if(sz[u] == 1) leaf[ls++] = u;
    chain[u] = chain[spc] = u;
    return sz[u];
}
node cmp(node u, node v)
{ return val[u] < val[v] ? v : u; }
void build()
{
    memset(sz, 0, sizeof sz); val[n] = INT_MIN;
    dfs(0, d[0]=ps=ls=0);
    for(int i=0;i<n;i++) chain[id[i]] = chain[chain[id[i]]];
    while(ls)
    {
        node u = leaf[--ls];
        while(u != chain[u])
            u = anc[tree[id[u]=ps++]=u];
        tree[id[u]=ps++] = u;
    }
    for(int i=n-1;i>0;--i) tree[i] = cmp(tree[i<<1],tree[i<<1|1]);
}
node t_query(int l, int r)
{
    node ans = n;
    for(;l<r;l>>=1,r>>=1)
    {
        if(l&1) ans = cmp(ans, tree[l++]);
        if(r&1) ans = cmp(ans, tree[--r]);
    }
    return ans;
}
void update(int p)
{
    if(!p) return;
    if(p >= n) p>>=1;
    tree[p] = cmp(tree[p<<1],tree[p<<1|1]);
    update(p>>1);
}
node query(node u, node v)
{
    node ans = n;
    while(chain[u] != chain[v])
    {
        if(d[chain[u]] < d[chain[v]]) swap(u,v);
        ans = cmp(ans, t_query(id[u], id[chain[u]]+1));
        u = anc[chain[u]];
    }
    if(d[u] < d[v]) swap(u,v);
    return cmp(ans, t_query(id[u],id[v]));
}

void prepare(node u, int v)
{
    val[u] = v;
    for(edge e=hd[u];e;e=nx[e])
        if(val[to[e]] == -1)
            prepare(to[e], w[e]);
}
int t;
int main()
{
    scanf(" %d", &t);
    while(t--)
    {
        memset(hd, 0, sizeof hd); es = 2;
        memset(val, -1, sizeof val);
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
        build();
        char cmd = 0;
        while(cmd != 'D')
        {
            scanf(" %c%*s", &cmd);
            if(cmd == 'D') continue;
            int x, y;
            scanf(" %d%d", &x, &y);
            if(cmd == 'Q')
                printf("%d\n", val[query(--x, --y)]);
            else
            {
                node u = to[x<<1],
                     v = to[x<<1|1],
                     t = d[u] < d[v] ? v : u;
                val[t] = y;
                update(id[t]);
            }
        }
    }
}
