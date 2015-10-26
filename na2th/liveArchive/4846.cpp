#include <bits/stdc++.h>
using namespace std;
typedef int num;
typedef int node;
typedef int edge;
const int MN = 2007;
const int ME = MN*MN;

int x[MN], y[MN], d[MN], hd[MN], cmp[MN], deg[MN];
int pre[MN], low[MN], pend[MN], ls, ps, prei;
int to[ME], nx[ME], es;
int t, n;

void dfs(node u)
{
    pre[u] = prei++;
    low[ls++] = pend[ps++] = u;
    for(edge e=hd[u];e!=-1;e=nx[e])
        if( pre[to[e]] == -1 )
            dfs(to[e]);
        else if( cmp[to[e]] == -1 )
        {
            while( pre[low[ls-1]] > pre[to[e]] )
                ls--;
        }
    if( low[ls-1] == u )
    {
        while( pend[ps-1] != u )
            cmp[pend[--ps]] = u;
        cmp[pend[--ps]] = u;
        ls--;
    }
}

int main()
{
    scanf(" %d", &t);
    while(t--)
    {
        scanf(" %d", &n);
        fill(hd , hd+n, -1);
        fill(pre, pre+n,-1);
        fill(deg, deg+n, 0);
        fill(cmp, cmp+n,-1);
        es = ls = ps = prei = 0;
        for(int i=0;i<n;i++)
            scanf(" %d%d%d", x+i, y+i, d+i);
        for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            if( i != j && 2*max(abs(x[i]-x[j]),abs(y[i]-y[j])) <= d[i] )
            {
                to[es] = j;
                nx[es] = hd[i];
                hd[i]  = es++;
            }

        for(node u=0;u<n;u++)
            if( pre[u] == -1 )
                dfs(u);

        for(node u=0;u<n;u++)
        {
            for(edge e=hd[u];e!=-1;e=nx[e])
                if( cmp[to[e]] != cmp[u] )
                    deg[cmp[to[e]]]++;
        }
        int ans = 0;
        for(node u=0;u<n;u++)
            if( u == cmp[u] )
                ans += ( deg[u] == 0 );
        printf("%d\n", ans);
    }
}
