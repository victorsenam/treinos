#include<bits/stdc++.h>
#define MV 1002
#define ME 20006
using namespace std;
typedef int num;
typedef int edge;
typedef int node;

num head[MV], dist[MV], anc[MV];
num to[ME], next[ME], cost[ME], es;
node source, dest, n, m;

void treeBuild( node s, node d )
{
    for( int i = 0; i < n; i++ )
        dist[i] = INT_MAX;
    set< pair<num, node> > reach;
    dist[s] = 0;
    anc[s]  = s;
    reach.insert( make_pair(0, s) );
    while( !reach.empty() )
    {
        node u = reach.begin()->second;
        reach.erase( reach.begin() );
        for( edge e = head[u]; e >= 0; e = next[e] )
            if( dist[to[e]] > dist[u] + cost[e] )
            {
                if( dist[to[e]] != INT_MAX )
                    reach.erase( reach.find(make_pair(dist[to[e]], to[e])) );
                anc[to[e]]  = u;
                dist[to[e]] = dist[u] + cost[e];
                reach.insert( make_pair(dist[to[e]], to[e] ) );
            }
    }
}

int main()
{
    scanf("%d %d", &n, &m); n+=2;
    memset( head, -1, sizeof head );
    es = 0;
    for( int i = 0; i < m; i++ )
    {
        node u, v; num c;
        scanf("%d %d %d", &u, &v, &c);
        to[es] = v; cost[es] = c; next[es] = head[u]; head[u] = es++;
        to[es] = u; cost[es] = c; next[es] = head[v]; head[v] = es++;
    }
    treeBuild(0, n-1);
    printf("%d\n", dist[n-1] );
}



