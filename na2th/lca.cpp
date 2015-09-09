#include<bits/stdc++.h>
using namespace std;
typedef int num;
typedef int node;
typedef int edge;
const int MV = 100000;
const int ME = 2*MV;

int head[MV], dpt[MV], tour[2*ME+2], pos[MV], ts;
int to[ME], next[ME], es;
int n;

inline int cmp(int a, int b)
{ return ( dpt[a] < dpt[b] ) ? a : b ;}

int dfs(node u, int d)
{
    dpt[u] = d;
    pos[u] = ts;
    tour[ts++] = u;
    for(edge e=head[u];e>=0;e=next[e])
        if( dpt[to[e]] == -1 )
        {
            dfs(to[e], dpt[u]+1);
            tour[ts++] = u;
        }
}

void build()
{
    memset(dpt, -1, sizeof dpt);
    ts = 2*n-1; dfs(0,0); dpt[n] = INT_MAX;
    for(int i=2*n-2; i>=0;--i)
        tour[i] = cmp(tour[i<<1], tour[i<<1|1]);
}

node lca(node u, node v)
{
    int l = min(pos[u], pos[v]),
        r = max(pos[u], pos[v])+1, ans = n;
    for(; l < r ; l>>=1, r>>=1)
    {
        if(l&1) ans = cmp(ans, tour[l++]);
        if(r&1) ans = cmp(ans, tour[--r]);
    }
    return ans;
}

int main()
{
    memset(head, -1, sizeof head);
    scanf("%d", &n);
    for(int i=0;i<n-1;i++)
    {
        node u,v; scanf("%d %d", &u, &v);
        to[es] = --v; next[es] = head[--u]; head[u] = es++;
        to[es] = u; next[es] = head[v]; head[v] = es++;
    }
    build();
    node u, v;
    while( scanf("%d %d", &u, &v) != EOF )
    {
        u--; v--;
        printf("lca(%d,%d) = %d\n", u+1, v+1, lca(u,v)+1);
    }
}
