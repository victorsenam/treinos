#include<bits/stdc++.h>
#define MV 101
#define ME 10002
using namespace std;
typedef int num;
typedef int node;
typedef int edge;

num head[MV], val[MV], label[MV], n, m;
num to[ME], next[ME], es;
node final;

num dfs(node s)
{
    label[s] = 1;
    final = s; node toVisit;
    if( head[s] == -1 )
        return val[s];
    else
        toVisit = head[s];

    for(edge e = head[s]; e>=0 ; e = next[e])
        if( label[to[e]] == 0 && val[to[e]] > val[toVisit] )
            toVisit = to[e];

    if( label[toVisit] == 1 )
        return val[s];

    return val[s] + dfs(toVisit);
}

int main()
{
    int tc;
    scanf("%d", &tc);
    for( int tcn=1; tcn < tc+1; tcn++ )
    {
        scanf("%d %d", &n, &m);
        es = 0;
        for( int i = 0; i < n; i++ )
        {
            scanf("%d", val+i);
            head[i]  = -1;
            label[i] = 0;
        }
        for( int i = 0; i < m; i++ )
        {
            node u,v; scanf("%d %d", &u, &v);
            to[es] = v; next[es] = head[u]; head[u] = es++;
        }
        num ans = dfs(0);
        printf("Case %d: %d %d\n", tcn,  ans, final);
    }
}
