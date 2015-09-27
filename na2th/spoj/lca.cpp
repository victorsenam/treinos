#include<bits/stdc++.h>
using namespace std;
typedef int num;
typedef int node;
typedef int edge;
const int MV = 1001;
const int ME = 2*MV;
int head[MV], pos[MV], dpt[MV], tour[4*MV], root[MV], ts;
int to[ME], next[ME], es;
int n,q;

node cmp(node u, node v)
{ return (dpt[u]<dpt[v])? u : v; }

void dfs(node u, int d)
{
    dpt[u] = d;
    pos[u] = ts;
    tour[ts++] = u;
    for(edge e=head[u];e>=0;e=next[e])
        if( dpt[to[e]] == -1 )
        {
            dfs(to[e], d+1);
            tour[ts++] = u;
        }
}

void build( node root )
{
    memset(dpt, -1, sizeof dpt);
    ts = 2*n-1; dfs(root, 0);
    dpt[n] = INT_MAX;
    for(int i=2*n-2; i>0;i--)
        tour[i] = cmp(tour[i<<1], tour[i<<1|1]);
}

node lca(node u, node v)
{
    int l = min(pos[u], pos[v]),
        r = max(pos[u], pos[v])+1;
    node ans = n;
    for(; l < r; l>>=1, r>>=1 )
    {
        if(l&1) ans = cmp(ans, tour[l++]);
        if(r&1) ans = cmp(ans, tour[--r]);
    }
    return ans;
}

int main()
{
    int tc;
    scanf("%d", &tc);
    for(int tcn=1;tcn<tc+1;tcn++)
    {
        scanf("%d", &n);
        memset(head, -1, sizeof head); es=0;
        for(int i=0;i<n;i++) root[i] = 1;
        for(node u=0;u<n;u++)
        {
            int aux; node v;
            scanf("%d", &aux);
            while(aux--)
            {
                scanf("%d", &v); v--;
                root[v] = 0;
                to[es] = v; next[es] = head[u]; head[u] = es++;
                to[es] = u; next[es] = head[v]; head[v] = es++;
            }
        }
        for(node v=0;v<n;v++)
            if(root[v])
                build(v);
        scanf("%d", &q);
        printf("Case %d:\n", tcn);
        while(q--)
        {
            node u,v;
            scanf("%d %d", &u, &v); u--; v--;
            printf("%d\n", lca(u,v)+1);
        }
    }
}
