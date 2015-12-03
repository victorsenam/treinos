#include<bits/stdc++.h>
#define MV 5002
#define ME 60003
typedef int num;
typedef unsigned long long ull;
typedef int node;
typedef int edge;
using namespace std;

int head[MV], dist[MV], curr[MV], Q[MV], vs;
int to[ME], next[ME], es;
num  cap[ME], flow[ME];
num n, m;

void add( node u, node v, num cuv, num cvu )
{
    to[es]   = v; flow[es]    = 0; cap[es]  = cuv;
    next[es] = head[u]; head[u] = es++;

    to[es]   = u; flow[es]    = 0; cap[es]  = cvu;
    next[es] = head[v]; head[v] = es++;
}

void bfs( node src )
{
    int qf=0, qb=0;
    for(int i=0; i<vs;i++) dist[i] = -1;
    dist[src] = 0;
    Q[qb++] = src;
    while( qf < qb )
    {
        node u = Q[qf++];
        for( edge e = head[u];e >= 0; e = next[e] )
            if( cap[e] > flow[e] && dist[to[e]] == -1 )
            {
                dist[to[e]] = dist[u] + 1;
                Q[qb++]     = to[e];
            }
    }
}

num dfs( node u, node g, num af )
{
    num ans;
    if( u == g ) return af;
    for( edge &e = curr[u]; e >= 0; e = next[e] )
        if( cap[e] > flow[e] && 
            dist[to[e]] == dist[u] + 1 && 
            (ans=dfs(to[e],g,min(af,cap[e]-flow[e])))>0 )
        {
            flow[e]   += ans;
            flow[e^1] -= ans;
            return ans;
        }
    return 0;
}

ull maxFlow( node src, node snk )
{
    ull ans = 0;
    for( bfs(src); dist[snk] != -1; bfs(src) )
    {
        for( int i = 0; i < vs; i++ ) curr[i] = head[i];
        while(42)
        {
            num nf = dfs( src, snk, INT_MAX );
            if( nf > 0 ) ans += nf;
            else break;
        }
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio( false );
    memset( head, -1, sizeof head); es = 0;
    cin >> n >> m; vs = n;
    while( m-- > 0 )
    {
        node u, v; num c;
        cin >> u >> v >> c;
        u--; v--;
        add(u, v, c, c);
    }
    cout << maxFlow(0,n-1) << endl;
}
