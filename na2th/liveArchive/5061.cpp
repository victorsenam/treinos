#include<bits/stdc++.h>
using namespace std;
typedef int num;
typedef int node;
typedef int edge;
const int MN = 50001;
const int ME = 2*MN;

int head[MN], anc[MN];
int to[ME], next[ME],es;
int tour[4*MN], pos[MN], dpt[MN+1], ts;
int sol[MN], lazy[MN];
int n, q;

node cmp(node u, node v)
{ return (dpt[u]<dpt[v]) ? u : v; }
void dfs(node u, int d)
{
    dpt[u] = d;
    pos[u] = ts;
    tour[ts++] = u;
    for(edge e=head[u];e>=0;e=next[e])
        if( dpt[to[e]] == -1 )
        {
            dfs(to[e], d+1);
            anc[to[e]] = u;
            tour[ts++] = u;
        }
}
void build(node root)
{
    memset(dpt, -1, sizeof dpt);
    ts = 2*n-1;
    dfs(root, 0);
    anc[root] = root;
    dpt[n] = INT_MAX;
    for(int i=2*n-1;i>0;i--)
        tour[i] = cmp(tour[i<<1],tour[i<<1|1]);
}
node lca(node u, node v)
{
    int l = min(pos[u], pos[v]),
        r = max(pos[u], pos[v])+1;
    node ans = n;
    for(;l<r;l>>=1,r>>=1)
    {
        if(l&1) ans = cmp(ans, tour[l++]);
        if(r&1) ans = cmp(ans, tour[--r]);
    }
    return ans;
}

num solve(node u)
{
    if( sol[u] == -1 )
    {
        sol[u] = lazy[u];
        for(edge e=head[u];e>=0;e=next[e])
            if( dpt[to[e]] > dpt[u] )
                sol[u] += solve(to[e]);
    }
    return sol[u];
}

int main()
{
    int tc, csn=1;
    scanf("%d", &tc);
    while(tc--)
    {
        memset(head, -1, sizeof head); es = 0;
        scanf("%d", &n);
        for(int i=0;i<n-1;i++)
        {
            node u,v; scanf("%d %d", &u, &v);
            to[es] = v; next[es] = head[u]; head[u] = es++;
            to[es] = u; next[es] = head[v]; head[v] = es++;
        }
        build(0);
        memset(lazy, 0, sizeof lazy);
        scanf("%d", &q);
        while(q--)
        {
            node u,v,a; int c;
            scanf("%d %d %d", &u, &v, &c);
            lazy[u] += c;
            lazy[v] += c;
            a = lca(u,v);
            lazy[a] -= c;
            if( anc[a] != a )
                lazy[anc[a]] -= c;
        }
        memset(sol, -1, sizeof sol);
        printf("Case #%d:\n", csn++);
        for(node u=0;u<n;u++)
            printf("%d\n", solve(u));
    }
}
