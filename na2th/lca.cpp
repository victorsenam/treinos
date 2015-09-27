#include<bits/stdc++.h>
using namespace std;
typedef int num;
typedef int node;
typedef int edge;
const int MV = 100000;
const int ME = 2*MV;

int head[MV];
int to[ME], next[ME], es;
int n;

int dpt[MV+1], seg[4*MV], pos[MV], ss;

inline node cmp(node u, node v)
{ return ( dpt[u] < dpt[v] ) ? u : v ;}

void dfs(node u, int d)
{
    dpt[u] = d;
    pos[u] = ss;
    seg[ss++] = u;
    for(edge e=head[u];e>=0;e=next[e])
        if( dpt[to[e]] == -1 )
        {
            dfs(to[e], dpt[u]+1);
            seg[ss++] = u;
        }
}

void build(node root)
{
    memset(dpt, -1, sizeof dpt);
    ss = 2*n-1;
    dfs(root,0);
    dpt[n] = INT_MAX;
    for(int i=2*n-2;i>0;--i)
        seg[i] = cmp(seg[i<<1], seg[i<<1|1]);
} // 5n - 4 operações

node lca(node u, node v)
{
    node ans = n;
    int l = min(pos[u], pos[v]),
        r = max(pos[u], pos[v])+1;
    for(; l < r ; l>>=1, r>>=1)
    {
        if(l&1) ans = cmp(ans, seg[l++]);
        if(r&1) ans = cmp(ans, seg[--r]);
    }
    return ans;
} // 2 + lg(n) operações

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
    build(0);
    node u, v;
    while( scanf("%d %d", &u, &v) != EOF )
    {
        u--; v--;
        printf("lca(%d,%d) = %d\n", u+1, v+1, lca(u,v)+1);
    }
}
