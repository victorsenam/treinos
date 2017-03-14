#include<bits/stdc++.h>
using namespace std;
typedef int node;
typedef int edge;
const int MV = 101+8;
const int ME = 2*5000;

int head[MV], low[MV], pre[MV], seen[MV], prei;
int to[ME], next[ME], es;
int ans, bdg, ncnt, goal, found, ok;
int m, n, t;

int dfs(node u, edge from)
{
    low[u] = pre[u] = prei++;
    ncnt++;
    for(edge e=head[u];e>=0;e=next[e])
    {
        if( low[to[e]] == -1  )
            low[u] = min(low[u], dfs(to[e], e^1));
        else if( e != from )
            low[u] = min(low[u], low[to[e]]);
    }
    if( low[u] == pre[u] && from != -1 )
    {
        found++;
        bdg = from;
    }
    return low[u];
}

void dfs_2(node u, int color)
{
    seen[u] = color;
    goal--;
    for(edge e=head[u];e>=0;e=next[e])
        if( e != bdg && e != (bdg^1) )
        {
            found++;
            if ( seen[to[e]] != color )
                dfs_2(to[e], color);
        }
}

int main()
{
    scanf("%d", &t);
    for(int tc=1;tc<t+1;tc++)
    {
        memset(head, -1, sizeof head); es = 0;
        memset(low, -1, sizeof low);
        memset(pre, -1, sizeof pre);
        memset(seen, -1, sizeof seen);
        ans = prei = 0;

        scanf(" %d%d", &n, &m);
        for(int i=0;i<m;i++)
        {
            node u, v;
            scanf(" %d%d", &u, &v);
            u--; v--;
            to[es] = v; next[es] = head[u]; head[u] = es++;
            to[es] = u; next[es] = head[v]; head[v] = es++;
        }
        for(node v=0;v<n;v++)
            if( low[v] == -1 )
            {
                bdg = -1;
                ok = 1;
                ncnt = found = 0;
                dfs(v, -1);
                if( ncnt%2 != 0 )
                    continue;
                if( ncnt > 4 )
                    ok &= ( found == 1 );
                else
                {
                    if( ncnt == 2 )
                        ans += ( found == 1 );
                    else
                        ans += ( found == 3 && ncnt == 4 );
                    continue;
                }
                if( !ok ) continue;

                ncnt /= 2;
                goal = ncnt;
                found = 0;
                dfs_2(to[bdg], to[bdg]);
                ok &= ( goal == 0 && found == ncnt*(ncnt-1) );

                goal = ncnt;
                found = 0;
                dfs_2(to[bdg^1], to[bdg^1]);
                ok &= ( goal == 0 && found == ncnt*(ncnt-1) );

                ans += ok;
            }
        printf("Case #%d: %d\n", tc, ans);
    }
}
