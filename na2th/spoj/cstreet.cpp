#include<bits/stdc++.h>
#define MV 1001
#define ME 600003
using namespace std;
typedef int num;
typedef int node;
typedef int edge;

int head[MV], dist[MV], eCost[MV], vs;
int to[ME], next[ME], cost[ME], es;
num t, p, n, m;

void buildTree( node src )
{
    fill(dist, dist+vs, -1);
    dist[src]  = 0;
    set<pair<num, node> > reach;
    reach.insert( make_pair(0, src) );
    while( !reach.empty() )
    {
        node u = reach.begin()->second;
        reach.erase( reach.begin() );
        eCost[u] = dist[u];
        dist[u]  = 0;
        for( edge e = head[u]; e >= 0; e = next[e] )
            if( dist[to[e]] == -1 || dist[to[e]] > dist[u] + cost[e] )
            {
                if( dist[to[e]] != -1 )
                    reach.erase( make_pair(dist[to[e]], to[e]) );
                dist[to[e]] = dist[u] + cost[e];
                reach.insert( make_pair(dist[to[e]], to[e] ));
            }
    }
}
int main()
{
    scanf("%d", &t);
    while( t-- > 0 )
    {
        scanf("%d %d %d", &p, &n, &m);
        memset(head, -1, sizeof head); es = 0;
        vs = n;
        while( m-- > 0 )
        {
            node u, v; num c;
            scanf("%d %d %d", &u, &v, &c); u--; v--;
            to[es] = v; cost[es] = c; next[es] = head[u]; head[u] = es++;
            to[es] = u; cost[es] = c; next[es] = head[v]; head[v] = es++;
        }
        buildTree(0);
        num ans = 0;
        for( int i = 1; i < vs; i++ )
            ans += eCost[i];
        printf("%d\n", p*ans);
    }
}
