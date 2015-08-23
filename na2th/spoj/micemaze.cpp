#include<bits/stdc++.h>
#define MV 100
#define ME (100*100)
using namespace std;
typedef int num;
typedef int node;
typedef int edge;

num head[MV], dist[MV];
num to[ME], next[ME], cost[ME], es;
num n, e ,t, m;

num treeBuild( node src )
{
    num ans = 0;
    fill(dist, dist+n, INT_MAX);
    set< pair<num, node> > reach;
    dist[src] = 0;
    reach.insert( make_pair(0, src) );
    while( !reach.empty() )
    {
        node u = reach.begin()->second;
        reach.erase( reach.begin() );
        if( dist[u] <= t )
            ans++;
        else return ans;
        for( edge e = head[u]; e >=0; e = next[e] )
            if( dist[to[e]] > dist[u] + cost[e] )
            {
                if( dist[to[e]] != INT_MAX )
                    reach.erase( make_pair(dist[to[e]], to[e]) );
                dist[to[e]] = dist[u] + cost[e];
                reach.insert( make_pair(dist[to[e]], to[e]) );
            }
    }
    return ans;
}

int main()
{
    scanf("%d %d %d %d", &n, &e, &t, &m); e--;
    fill( head, head + n, -1); es = 0;
    for( int i = 0; i < m; i++ )
    {
        node u, v; num c;
        scanf("%d %d %d", &u, &v, &c); u--;v--;
        to[es] = u; cost[es] = c; next[es] = head[v]; head[v]= es++;
    }
    printf("%d\n", treeBuild(e));
}

