#include<bits/stdc++.h>
#define MV 101
#define ME (102*101)
using namespace std;
typedef int num;
typedef int edge;
typedef int node;

num head[MV], dist[MV], anc[MV];
num to[ME], next[ME], cost[ME], es;
node n, m;

void treeBuild( node s )
{
    for( int i = 0; i < n ; i++ )
        dist[i] = INT_MAX;
    set< pair<num, node> > reach;
    dist[s] = 0;
    anc[s]  = s;
    reach.insert( make_pair(0, s) );
    while( !reach.empty() )
    {
        node u  = reach.begin()->second;
        reach.erase( reach.begin() );
        dist[u] = 0; // Prim
        for( edge e = head[u]; e >= 0; e = next[e] )
            if( dist[to[e]] > dist[u] + cost[e] )
            {
                if( dist[to[e]] != INT_MAX )
                    reach.erase( reach.find( make_pair(dist[to[e]], to[e])) );
                dist[to[e]] = dist[u] + cost[e];
                anc[to[e]]  = u;
                reach.insert( make_pair(dist[to[e]], to[e]) );
            }
    }
}

int main()
{
    int tc = 1;
    while( scanf("%d %d", &n, &m) != EOF && n && m )
    {
        printf("Teste %d\n", tc++ );
        memset( head, -1, sizeof head ); es = 0;
        for( int i = 0; i < m; i++ )
        {
            node u, v; num c;
            scanf("%d %d %d", &u, &v, &c); u--; v--;
            to[es] = v; cost[es] = c; next[es] = head[u]; head[u] = es++;
            to[es] = u; cost[es] = c; next[es] = head[v]; head[v] = es++;
        }
        treeBuild(0);
        for( int i = 1; i < n; i++ )
            printf("%d %d\n", min(i, anc[i])+1, max(i, anc[i])+1);
        printf("\n");
    }
}


