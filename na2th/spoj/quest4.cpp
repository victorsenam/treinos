#include <bits/stdc++.h>
#define MV 250 
#define ME 20505
using namespace std;
typedef int num;
// [0,119]   rows
// [120,239] columns
// [240]     source
// [241]     sink

num tc, n;
num cap[ME], to[ME], next[ME], es;
num head[MV], dist[MV], curr[MV], vs=250;

void add( int u, int v, int c )
{
    cap[es]  = c;
    to[es]   = v;
    next[es] = head[u];
    head[u]  = es++;

    cap[es]  = 0;
    to[es]   = u;
    next[es] = head[v];
    head[v]  = es++;
}

void findSink(num s, num t)
{
    fill( dist, dist+vs, -1);
    dist[s] = 0;
    queue<num> toVisit; toVisit.push( s );
    while ( !toVisit.empty() )
    {
        num u = toVisit.front(); toVisit.pop();
        for( num e = head[u]; e >= 0 ; e = next[e] )
            if( cap[e] > 0 && dist[to[e]] == -1 )
            {
                dist[to[e]] = dist[u] + 1;
                toVisit.push( to[e] );
            }
    }
}

num getFlow( num v, num t, num af )
{
    if( v == t ) return af;

    num nf;
    for( num &e = curr[v] ; e >= 0 ; e = next[e] )
        if( cap[e] > 0 && dist[to[e]] == dist[v] + 1 )
            {
                nf = getFlow( to[e], t, min(af, cap[e]) );
                if( nf > 0 )
                {
                    cap[e] -= nf;
                    cap[e^1] += nf;
                    return nf;
                }
            }
    return 0;
}

num maxFlow( num s, num t )
{
    num ans = 0;
    for( findSink(s, t); dist[t] != -1 ; findSink(s, t))
    {
        for( int i = 0; i < vs; i++ )
            curr[i] = head[i];
        while ( true )
        {
            num mf = getFlow(s, t, INT_MAX);
            if( mf == 0 ) break;
            else ans += mf;
        }
    }
    return ans;
}

int main()
{
    int tc;
    scanf("%d", &tc);
    while( tc-- > 0 )
    {
        int e;
        scanf("%d", &e);
        es = 0;
        for( int i = 0; i < vs; i++ )
            head[i] = -1;
        for( int i = 0; i < 120; i++ )
        {
            add(  240,   i, 1);
            add(120+i, 241, 1);
        }

        while( e-- > 0 )
        {
            int x, y; scanf("%d %d", &x, &y);
            add(x, 120+y,1);
        }
        printf("%d\n", maxFlow(240, 241));
    }
}
