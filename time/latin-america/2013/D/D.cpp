#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef int node;
typedef int edge;

const int N = 1e3+7;
const int M = 1e5+7;
const int T = (N+M)<<1;

int hd[N];
int to[M], nx[M], es;

int n,m,ps,ans;
int id[N], d[N];
node tree[T];

inline node cmp(node u, node v)
{ return d[u] < d[v] ? u : v; }
void build(node u, int d)
{
    tree[id[u]=ps++] = u;
    ::d[u] = d;
    for(edge e=hd[u];e!=-1;e=nx[e])
        if(::d[to[e]] == -1)
        {
            build(to[e], d+1);
            tree[ps++] = u;
        }
}
int lca(node u, node v)
{
    if(id[u] > id[v]) swap(u,v);
    int l = id[u], r = id[v]+1, ans = n;
    for(;l<r;l>>=1,r>>=1)
    {
        if(l&1) ans = cmp(ans, tree[l++]);
        if(r&1) ans = cmp(ans, tree[--r]);
    }
    return ans;
}


int main() {
    while(scanf(" %d%d", &n, &m) != EOF)
    {
        memset(hd, -1, sizeof hd);
        memset(d,  -1, sizeof  d);
        es = 0;
        for(int i=0;i<m;i++)
        {
            node u, v;
            scanf(" %d%d", &u, &v); --u; --v;
            to[es] = v; nx[es] = hd[u]; hd[u] = es++;
        }
        ps = n+m;
        d[n] = INT_MAX;
        build(0,0);
        for(int i=n+m-1;i>=0;--i) tree[i] = cmp(tree[i<<1],tree[i<<1|1]);
        for(node u=0;u<n;u++)
            for(node v=u+1;v<n;v++)
                if(lca(u,v) != 0)
                {
                    printf("%d %d %d\n", u+1, v+1, lca(u,v)+1);
                    ans++;
                }
        printf("%d\n", ans);
        putchar('\n');
    }
}

