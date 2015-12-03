#include <bits/stdc++.h>
#define MV 203
#define ME 40000
using namespace std;
typedef int num;

num n;
num cap[ME], to[ME], next[ME], es;
num head[MV], dist[MV], curr[MV], vs;

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

num getFlow( num v, num af )
{
    if( v == n-1 ) return af;

    num nf;
    for( num &e = curr[v] ; e >= 0 ; e = next[e] )
        if( cap[e] > 0 && dist[to[e]] == dist[v] + 1 )
            {
                nf = getFlow( to[e], min(af, cap[e]) );
                if( nf > 0 )
                {
                    cap[e] -= nf;
                    cap[e^1] += nf;
                    return nf;
                }
            }
    return 0;
}

num maxFlow( num s, num t)
{
    num ans = 0;
    for( findSink(s, t); dist[t] != -1 ; findSink(s, t))
    {
        for( int i = 0; i < vs; i++ )
            curr[i] = head[i];
        while ( true )
        {
            num mf = getFlow(s, INT_MAX);
            if( mf == 0 ) break;
            else ans += mf;
        }
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio( false );
    num t, aux, v;
    cin >> t;
    while( t-- > 0 )
    {
        cin >> n;
        // Limpa arestas
        es = 0;
        vs = n;
        fill( head, head + n, -1);

        for( int i = 0; i < n-1; i++ )
        {
            cin >> aux;
            while ( aux-- > 0 )
            {
                cin >> v; v--;
                if( i == 0 || v == n-1 )
                    add( min(i,v), max(i,v), 1);
                else
                    add( min(i,v), max(i,v), INT_MAX);
            }
        }
        cout << maxFlow(0, n-1) << endl;
    }
}
