#include<bits/stdc++.h>
#define MV 1000
#define EPS 1e-9
using namespace std;
typedef int num;
typedef int node;
// Sem edges, grafo dado implicitamente

node anc[MV];
double x[MV], y[MV], dist[MV];
num done[MV], n;

inline double cost( node u, node v )
{ return sqrt( (x[u]-x[v])*(x[u]-x[v]) + (y[u]-y[v])*(y[u]-y[v]) ); }

void treeBuild( node source )
{
    for( int i = 0; i < n; i++ )
        dist[i] = DBL_MAX;
    dist[source] = 0;
    anc[source]  = source;
    set< pair<double, node> > reach;
    reach.insert( make_pair(0.0, source) );
    while( !reach.empty() )
    {
        node u = reach.begin()->second;
        reach.erase( reach.begin() );
        dist[u] = 0.0;
        for( int i = 0; i < n; i++ )
            if( i != u && dist[i] > dist[u] + cost(u,i) )
            {
                if( dist[i] < DBL_MAX )
                    reach.erase( make_pair(dist[i], i) );
                anc[i]  = u;
                dist[i] = dist[u] + cost(u,i);
                reach.insert( make_pair(dist[i], i));
            }
    }
}

int main()
{
    while( scanf("%d", &n) != EOF && n )
    {
        for( int i = 0; i < n; i++ )
        {
            double ix, iy; scanf(" %lf %lf", &ix, &iy);
            x[i] = ix; y[i] = iy;
        }

        treeBuild( 0 );
        double ans = 0.0;
        for( int i = 1; i < n; i++ )
            ans = max( ans, cost(anc[i], i) );
        printf("%.4lf\n", ans);
    }
}
