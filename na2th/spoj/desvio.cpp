#include<bits/stdc++.h>
#define MV 251
#define ME (128*251)
using namespace std;
typedef int num;
typedef int edge;
typedef int node;

edge head[MV];
num  dist[MV];

edge next[ME];
node to[ME];
num  cost[ME], es;

num n, m, c, k;

void buildTree( node start, node dest )
{
    for( int i = 0; i < n; i++ )
        dist[i] = INT_MAX;
    dist[start] = 0;
    set< pair<num, node> > reach;
    reach.insert( make_pair(0, start) );
    while( !reach.empty() )
    {
        node u = reach.begin()->second;
        if( u == dest ) break;
        reach.erase( reach.begin() );
        for( edge e = head[u]; e >= 0; e = next[e] )
            if( dist[to[e]] > dist[u] + cost[e] )
            {
                if( dist[to[e]] != INT_MAX )
                    reach.erase( make_pair(dist[to[e]], to[e]) );
                dist[to[e]] = dist[u] + cost[e];
                reach.insert( make_pair(dist[to[e]], to[e]));
            }
    }
}

int main()
{
    while( scanf("%d %d %d %d", &n, &m, &c, &k) != EOF && n )
    {
        memset( head, -1, sizeof head ); es = 0;
        for( int i = 0; i < m; i++ )
        {
            node u, v; num p;
            scanf("%d %d %d", &u, &v, &p);
            if( u > v ) swap(u,v);
            
            // Adiciona u -> v SSE u + 1 == v
            if ( v < c && u + 1 < v ) continue;
            else if( v < c )
            {
                to[es] = v; cost[es] = p; next[es] = head[u]; head[u] = es++;
            }
            else if( u < c ) // Adiciona de v -> u 
            {
                to[es] = u; cost[es] = p; next[es] = head[v]; head[v] = es++;
            }
            else // Adiciona ambas
            {
                to[es] = v; cost[es] = p; next[es] = head[u]; head[u] = es++;
                to[es] = u; cost[es] = p; next[es] = head[v]; head[v] = es++;
            }
        }
        buildTree( k, c-1 );
        printf("%d\n", dist[c-1]);
    }
}
